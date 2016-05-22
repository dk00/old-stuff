#!/usr/bin/env python
doc_class = '\documentclass[10pt,twocolumn,oneside]{article}'
head = '''\\usepackage{amsmath}
\\topmargin=0pt
\\headheight=0pt
\\headsep=5pt
\\textheight=750pt
\\footskip=0pt
\\voffset=-40pt
\\textwidth=520pt
\\marginparsep=0pt
\\marginparwidth=0pt
\\marginparpush=0pt
\\oddsidemargin=0pt
\\evensidemargin=0pt
\\hoffset=-30pt

\\begin{document}
\\tableofcontents
\\scriptsize
'''
tail = '\\end{document}'
src_types = ['.c', '.C', '.cpp', '.CPP']
import os
import sys
import subprocess
outname = 'book.tex'
sys.stdout = open(outname, 'w')
print doc_class
print head
for root, dirs, files in os.walk('.'):
  if os.path.basename(root) != '.':
    print '\\section{' + os.path.basename(root) + '}'
  for name in files:
    base, ext = os.path.splitext(name)
    if ext not in src_types:
      continue
    print '\\subsection{' + base + '}'
    print '\\begin{verbatim}'
    f = open(root + '/' + name)
    print f.read()
    f.close()
    print '\\end{verbatim}'
print tail
sys.stdout.flush()
subprocess.call(['bg5pdflatex', outname])
