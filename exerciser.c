#include "exerciser.h"

void exercise(MYSQL* conn)
{
  query1(conn, 1,10,20,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0);
  printf("\n\n");
  query2(conn, "Red");
  printf("\n\n");
  query3(conn, "Duk");
  printf("\n\n");
  query4(conn, "NC", "DarkBlue");
  printf("\n\n");
  query5(conn, 10);
  printf("\n\n");
  add_player(conn, 1, 88, "Guotao", "Dong", 50, 50, 30, 10, 10.8, 8.8);
  printf("\n\n");
  add_team(conn, "first round", 1, 3, 10, 1);
  printf("\n\n");
  add_state(conn, "JP");
  printf("\n\n");
  add_color(conn, "PURPLE");
  printf("\n\n");
  
}
