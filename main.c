#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exerciser.h"

int check(char* str) {
  int res = 1;
  int len = strlen(str);
  for (int i = 0; i < len-1; i++) {
    if (str[i] != ' ') {
      res = 0;
    }
  }
  return res;
}
void delLine(char** str_array, int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < strlen(str_array[i]); j++ ) {
      if (str_array[i][j] == '\n') {
	str_array[i][j] = ' ';
      }
    }
  }
}
void addComma(char** str_array, int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < strlen(str_array[i]); j++) {
      if (str_array[i][j] == ' ') {
	str_array[i][j] = ',';
      }
    }
  }
}
void insertTable(char* table, MYSQL* conn, char** str_array, int m) {
  char* pre = "insert into ";
  char* mid =  " values (";
  char* post = ");";
  char* comma = ", ";
  char** init = malloc(m * sizeof(char*));
  for (int i = 0; i < m; i++) {
    init[i] = malloc(500 * sizeof(char));
    strcat(init[i], pre);
    strcat(init[i], table);
    strcat(init[i], mid);
    char* tok = strtok(str_array[i], " ");
    while (tok) {
      if ( (int)*tok >= 65 && (int)*tok <= 90) {
	strcat(init[i], "'");
	strcat(init[i], tok);
	strcat(init[i], "'");
      } else {
	strcat(init[i], tok);
      }
      strcat(init[i], comma);
      tok = strtok(NULL, " '\n'");
    }
    init[i][strlen(init[i]) - 2] = '\0';
    strcat(init[i], post);
    //printf("%s\n", init[i]);
    if (mysql_query(conn, init[i])) {
      exit_with_error(conn);
    }
  }
}

int main (int argc, char *argv[]) {
  //Allocate & initialize a MYSQL object
  MYSQL *conn = mysql_init(NULL); 

  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
  }

  //Establish a connection to the database
  //Parameters: connection handler, host name, user name, password,
  //            database name, port numbrer, unix socket, client flag
  if (mysql_real_connect(conn, "localhost", "myuser", "passw0rd", "ACC_BBALL", 0, NULL, 0) == NULL) {
    exit_with_error(conn);
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  //read contents from each .txt
  char* line;
  size_t len = 0;
  size_t read;
  //read rows from team.txt
  FILE* fd1 = fopen("team.txt", "r");
  if (fd1 == NULL) {
    perror("Failed to open team.txt");
  }
  int t = 0;
  char** team = malloc(sizeof(char*));
  while (read = getline(&line, &len, fd1) != -1) {
    if (check(line) == 0) {
      team = (char**)realloc(team, (t+1) * sizeof(char*));
      team[t] = malloc(sizeof(line));
      team[t] = strdup(line);
      t++;
    }
    line = NULL;
  }
  if (fclose(fd1) != 0) {
    perror("Failed to close team.txt");
  }
  //read rows from player.txt
  FILE* fd2 = fopen("player.txt", "r");
  if (fd2 == NULL) {
    perror("Failed to open player.txt");
  }
  int p = 0;
  char** player = malloc(sizeof(char*));
  while (read = getline(&line, &len, fd2) != -1) {
    if (check(line) == 0) {
      player = (char**)realloc(player, (p+1) * sizeof(char*));
      player[p] = malloc(sizeof(line));
      player[p] = strdup(line);
      p++;
    }
    line = NULL;
  }
  if (fclose(fd2) != 0) {
    perror("Failed to close player.txt");
  }
  //read rows from state.txt
  FILE* fd3 = fopen("state.txt", "r");
  if (fd2 == NULL) {
    perror("Failed to open state.txt");
  }
  int s = 0;
  char** state = malloc(sizeof(char*));
  while (read = getline(&line, &len, fd3) != -1) {
    if (check(line) == 0) {
      state = (char**)realloc(state, (p+1) * sizeof(char*));
      state[s] = malloc(sizeof(line));
      state[s] = strdup(line);
      s++;
    }
    line = NULL;
  }
  if (fclose(fd3) != 0) {
    perror("Failed to close state.txt");
  }
  //read rows from color.txt
  FILE* fd4 = fopen("color.txt", "r");
  if (fd4 == NULL) {
    perror("Failed to open color.txt");
  }
  int c = 0;
  char** color = malloc(sizeof(char*));
  while (read = getline(&line, &len, fd4) != -1) {
    if (check(line) == 0) {
      color = (char**)realloc(color, (c+1) * sizeof(char*));
      color[c] = malloc(sizeof(line));
      color[c] = strdup(line);
      c++;
    }
    line = NULL;
  }
  if (fclose(fd4) != 0) {
    perror("Failed to close color.txt");
  }
  //create table for team
  if(mysql_query(conn, "drop table if exists TEAM;")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  if(mysql_query(conn, "create table if not exists TEAM(TEAM_ID INT UNSIGNED NOT NULL AUTO_INCREMENT, NAME VARCHAR(50), STATE_ID INT UNSIGNED, COLOR_ID INT UNSIGNED, WINS INT UNSIGNED, LOSSES INT UNSIGNED, PRIMARY KEY(TEAM_ID));")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  //create table for player
  if(mysql_query(conn, "drop table if exists PLAYER;")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  if(mysql_query(conn, "create table if not exists PLAYER(PLAYER_ID INT UNSIGNED NOT NULL AUTO_INCREMENT, TEAM_ID INT UNSIGNED, UNIFORM_NUM INT UNSIGNED, FIRST_NAME VARCHAR(30), LAST_NAME VARCHAR(30), MPG INT UNSIGNED, PPG INT UNSIGNED, RPG INT UNSIGNED, APG INT UNSIGNED, SPG DECIMAL(2,1), BPG DECIMAL (2,1), PRIMARY KEY(PLAYER_ID));")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  // create table for state
  if(mysql_query(conn, "drop table if exists STATE;")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  if (mysql_query(conn, "create table if not exists STATE(STATE_ID INT UNSIGNED AUTO_INCREMENT, NAME VARCHAR(30), PRIMARY KEY(STATE_ID));")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  //create table for color
  if(mysql_query(conn, "drop table if exists COLOR;")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  if (mysql_query(conn, "create table if not exists COLOR(COLOR_ID INT UNSIGNED AUTO_INCREMENT, NAME VARCHAR(30), PRIMARY KEY(COLOR_ID));")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return -1;
  }
  //insert into table team
  insertTable("TEAM", conn, team, t);
  insertTable("PLAYER", conn, player, p);
  insertTable("STATE", conn, state, s);
  insertTable("COLOR", conn, color, c);
  
  



  exercise(conn);


  //Close database connection
  mysql_close(conn);

  return 0;
}


