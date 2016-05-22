#ifdef _DV_ALGO_H
#define _DV_ALGO_H
#include<vector>
using namespace std;
class dv_algo {
public:
  virtual bool route(vector<unsigned> dis, unsigned from_id,
      const vector<unsigned>& from_dis);
};
#endif
