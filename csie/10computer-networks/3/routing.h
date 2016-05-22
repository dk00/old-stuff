class Routing {
public:
  Routing();
  void Init(int id);
  virtual bool Update(int id, int cost);
  const int *GetDis();
private:
  int dis[256];
};

struct RoutingMes {

};
