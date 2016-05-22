/**
  * @author Tz-Huan Huang <tzhuan AT gmail DOT com>
  * @brief A toy machine implementation 
  *
  * This is an X-TOY virtual machine implementation.
  * (http://www.cs.princeton.edu/introcs/xtoy/index.html)
  * 
  * Note: because of the memory layout, this implementation only runs
  *       correctly on little-endian processor such as intel x86.
  *
  * Usage: 
  *   Toy<short> toy(cin);  // get instance and read from stdard input
  *   toy(x); // the content of memory at address x
  *   toy[y]; // the content of register y
  *   toy.step(); // execute a step
  *   toy.run(N); // execute until finish or exceed N steps or exception thrown
  *   toy.reset(); // reset the toy machine
  *
  *   // for debug
  *   toy.dump_R(); // dump the contents of all registers
  *   toy.dump_mem(); // dump the contents of all memories
  */

#ifndef __TOY_H__
#define __TOY_H__

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cerrno>

#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

namespace toy {
	static const size_t RegisterSize = 16;
	static const size_t MemorySize = 256;
	static const size_t EntryPoint = 0x10;

	using namespace std;

	template<typename word>
	class Toy {
		public:
			typedef size_t size_type;

			/**
			  * @brief Constructor of Toy
			  *
			  * @param b input stream of the binary to be execute
			  * @param i input stream for standard input, default to cin
			  * @param o output stream for standard output, default to cout
			  * @param e output stream for standard error output, default to cerr
			  */
			Toy(istream &b, // {{{
				istream &i = cin, 
				ostream &o = cout, 
				ostream &e = cerr)
				: in(i), out(o), err(e)
			{
				fill(R, R + RegisterSize, 0);
				fill(mem, mem + MemorySize, 0);
				fill(binary, binary + MemorySize, 0);
				read_binary(b);
				//dump_R();
				//dump_mem();
				reset();
			} // }}}
			~Toy() {}

			/**
			  * @brief Get/set the content of memory at address i
			  *
			  * @param i memory address
			  */
			word& operator ()(size_type i) // {{{
			{
				if (i >= MemorySize)
					throw runtime_error("Error: Segmentation fault");
				return mem[i];
			} 
			const word& operator ()(size_type i) const 
			{
				if (i >= MemorySize)
					throw runtime_error("Error: Segmentation fault");
				return mem[i];
			} // }}}

			/**
			  * @brief Get/set the content of register i
			  *
			  * @param i register number
			  */
			word& operator [](size_type i) // {{{
			{
				if (i >= RegisterSize)
					throw runtime_error("Error: Instruction error");
				return R[i];
			} 
			const word& operator [](size_type i) const 
			{
				if (i >= RegisterSize)
					throw runtime_error("Error: Instruction error");
				return R[i];
			} // }}}

			/** @brief Execute a step
			  */
			bool step() // {{{
			{
				// err << "pc: " << pc << endl;
				// dump_R();

				// finished
				if (pc == -1) return false;

				// Fetch and parse
				word inst = mem[pc++];	// fetch next instruction
				word op   = (inst >> 12) &  0xf;	// get opcode (bits 12-15)
				word d    = (inst >>  8) &  0xf;	// get dest   (bits  8-11)
				word s    = (inst >>  4) &  0xf;	// get s      (bits  4- 7)
				word t    = (inst >>  0) &  0xf;	// get t      (bits  0- 3)
				word addr = (inst >>  0) & 0xff;	// get addr   (bits  0- 7)

				// halt
				if (op == 0) {
					pc = -1;
					return false;
				}

				// stdin 
				if ((addr == 255 && op == 8) || (R[t] == 255 && op == 10)) {
					mem[255] = 0;
					string input;
					for (size_type i = 0; i < 4; ++i) {
						char c;
						in >> c;
						input += c;
					}
					word data;
					if (! str2word(input.c_str(), data)) {
						throw runtime_error("Error: Input error");
					}
					mem[255] = data;
				}

				// Execute
				switch (op) {
					case  1: R[d] = R[s] +  R[t];       break;    // add
					case  2: R[d] = R[s] -  R[t];       break;    // subtract
					case  3: R[d] = R[s] &  R[t];       break;    // bitwise and
					case  4: R[d] = R[s] ^  R[t];       break;    // bitwise xor
					case  5: R[d] = R[s] << R[t];       break;    // shift left
					case  6: R[d] = R[s] >> R[t];       break;    // shift right
					case  7: R[d] = addr;               break;    // load address
					case  8: R[d] = mem[addr];          break;    // load
					case  9: mem[addr] = R[d];          break;    // store
					case 10: R[d] = mem[R[t] & 255];    break;    // load indirect
					case 11: mem[R[t] & 255] = R[d];    break;    // store indirect
					case 12: if (R[d] == 0) pc = addr;	break;    // branch if zero
					case 13: if (R[d] >  0) pc = addr;  break;    // branch if positive
					case 14: pc = R[d];                 break;    // jump indirect
					case 15: R[d] = pc; pc = addr;      break;    // jump and link
				}

				// stdout
				if ((addr == 255 && op == 9) || (R[t] == 255 && op == 11)) {
					out << setfill('0') << setw(4) << setbase(16) 
						<< mem[255] << endl;
					/*
					for (size_type i = 0; i < 4; ++i) {
						char c = mem[255] << (i*4) >> 12;
						out << setbase(16) << (word)c;
					}
					out << endl;
					*/
				}

				R[0] = 0;                // make sure R0 is always 0
				R[d] = R[d] & 0xFFFF;    // don't let R[d] overflow a 16-bit integer (needed???)
				pc = pc & 255;           // don't let pc overflow an 8-bit integer
				return true;
			} // }}}

			/** @brief Execute until finish or step limitation exceeded or 
			  *        exception thrown
			  * @param limit step limitation, default to numeric_limits<size_type>::max()-1
			  */
			size_type run(size_type limit = std::numeric_limits<size_type>::max()-1) // {{{
			{
				reset();
				size_type i = 1;
				while (step()) {
					++i;
					if (i > limit) 
						throw runtime_error("Error: Out of CPU time");
				}
				return i;
			} // }}}

			/** @brief Reset the Toy machine
			  */
			void reset() // {{{
			{
				pc = EntryPoint;
				copy(mem, mem + MemorySize, binary);
			} // }}}

			/** @brief Dump the contents of all registers, for debug
			  */
			void dump_R() // {{{
			{
				for (size_type i = 0; i < RegisterSize; ++i) {
					err << "R[" << setbase(16) << i << "]: 0x" 
						<< setfill('0') << setw(4) << setbase(16) << R[i] 
						<< " (" << setbase(10) << R[i] << ")" << endl;
				}
			} // }}}

			/** @brief Dump the contents of all memory, for debug
			  */
			void dump_mem() // {{{
			{
				for (size_type i = 0; i < MemorySize;) {
					err << "mem[" 
						<< setw(2) << setfill('0') << setbase(16) << i
						<< "]:";
					for (size_type j = 0; j < 4; ++j, ++i) {
						err << ' ' 
							<< setw(4) << setfill('0') << setbase(16) << mem[i];
					}
					err << endl;
				}
			} // }}}
		protected:
			void read_binary(istream &b) // {{{
			{
				string::size_type npos = string::npos;
				const string whitespace(" \t\n\r");

				ostringstream os;
				int line_no = 0;

				while (b.good()) { // {{{
					line_no++;
					string src, line;

					getline(b, src);
					line = src;

					string::size_type pos;

					// remove comments
					if (( pos = line.find("//") ) != string::npos)
						line = line.substr(0, pos);

					// trim
					if (( pos = line.find_first_not_of(whitespace) ) != npos)
						line = line.substr(pos);
					if (( pos = line.find_last_not_of(whitespace) ) != npos)
						line = line.substr(0, pos + 1);

					// err << "  {" << src << "}" << endl;

					// next if empty
					if (line == "") continue;

					if (( pos = line.find(":") ) == npos) {
						os << "Error: Load binary error: " 
							<< line_no << ": " << src << endl;
						continue;
					}

					word address, data;

					// get address
					if (! str2word(line.substr(0, pos), address)) {
						os << "Error: Load binary error: " 
							<< line_no << ": " << src << endl;
						continue;
					}

					if (( pos = line.find_first_not_of(whitespace, pos + 1) )
							== npos) {
						os << "Error: Load binary error: " 
							<< line_no << ": " << src << endl;
						continue;
					}

					string str_data = line.substr(pos);
					if (str_data.size() != 4) {
						os << "Error: Load binary error: " 
							<< line_no << ": " << src << endl;
						continue;
					}
					// get data
					if (! str2word(str_data, data)) {
						os << "Error: Load binary error: " 
							<< line_no << ": " << src << endl;
						continue;
					}

					// err << "[" << setbase(16) << address << "] - [" << setbase(16) << data << "]" << endl;
					operator()(address) = data;
				} // }}}
				if (os.str().size() > 0) throw runtime_error(os.str());
			} // }}}
			bool str2word(const string &from, word &to) const // {{{
			{
				to = static_cast<word>(strtol(from.c_str(), 0, 16));
				return (to != 0 || errno != ERANGE);
			} // }}}

		private:
			word pc;
			word R[RegisterSize];
			word mem[MemorySize];
			word binary[MemorySize];

			istream &in;
			ostream &out;
			ostream &err;
	};
} // namespace toy

#endif // __TOY_H__
