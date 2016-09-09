#include "query_funcs.h"

void exit_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}
void add_player(MYSQL *conn, int team_id, int jersey_num, char *first_name, char *last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "insert into PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) values (");
  char team[10];
  sprintf(team, "%d", team_id);
  strcat(query, team);
  strcat(query, ", ");
  char uniform[10];
  sprintf(uniform, "%d", jersey_num);
  strcat(query, uniform);
  strcat(query, ", '");
  strcat(query, first_name);
  strcat(query, "', '");
  strcat(query, last_name);
  strcat(query, "', ");
  char m[10];
  sprintf(m, "%d", mpg);
  strcat(query, m);
  strcat(query, ", ");
  char p[10];
  sprintf(p, "%d", ppg);
  strcat(query, p);
  strcat(query, ", ");
  char r[10];
  sprintf(r, "%d", rpg);
  strcat(query, r);
  strcat(query, ", ");
  char a[10];
  sprintf(a, "%d", apg);
  strcat(query, a);
  strcat(query, ", ");
  char s[10];
  sprintf(s, "%f", spg);
  strcat(query, s);
  strcat(query, ", ");
  char b[10];
  sprintf(b, "%f", bpg);
  strcat(query, b);
  strcat(query, ")");
  strcat(query, end);
  //printf("query is:\n %s\n", query);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  free(query);
}


void add_team(MYSQL *conn, char *name, int state_id, int color_id, int wins, int losses)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "insert into TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) values ('");
  strcat(query, name);
  strcat(query, "', ");
  char state[10];
  sprintf(state, "%d", state_id);
  strcat(query, state);
  strcat(query, ", ");
  char color[10];
  sprintf(color, "%d", color_id);
  strcat(query, color);
  strcat(query, ", ");
  char win[10];
  sprintf(win, "%d", wins);
  strcat(query, win);
  strcat(query, ", ");
  char loss[10];
  sprintf(loss, "%d", losses);
  strcat(query, loss);
  strcat(query, ")");
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  free(query);
}


void add_state(MYSQL *conn, char *name)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "insert into STATE (NAME) values ('");
  strcat(query, name);
  strcat(query, "')");
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  free(query);
}


void add_color(MYSQL *conn, char *name)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "insert into COLOR (NAME) values ('");
  strcat(query, name);
  strcat(query, "')");
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  free(query);
}


void query1(MYSQL *conn,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  char* query = NULL;
  char* start = "select * from player where ";
  char* and = " and ";
  char* end = ";";
  if (use_mpg == 1) {
    if (query == NULL) {
      query = malloc(1000 * sizeof(char));
      query[0] = '\0';
    }
    strcat(query, start);
    char* greater = "mpg >= ";
    strcat(query, greater);
    char num_min[10];
    sprintf(num_min, "%d", min_mpg);
    strcat(query, num_min);
    strcat(query, and);
    char* less = "mpg <= ";
    strcat(query, less);
    char num_max[10];
    sprintf(num_max, "%d", max_mpg);
    strcat(query, num_max);
  }
  if (use_ppg == 1) {
    if (query == NULL) {
      query = malloc(1000 * sizeof(char));
      query[0] = '\0';
    }
    strcat(query, and);
    char* greater = "ppg >= ";
    strcat(query, greater);
    char num_min[10];
    sprintf(num_min, "%d", min_ppg);
    strcat(query, num_min);
    strcat(query, and);
    char* less = "ppg <= ";
    strcat(query, less);
    char num_max[10];
    sprintf(num_max, "%d", max_ppg);
    strcat(query, num_max);
  }
  if (use_rpg == 1) {
    if (query == NULL) {
      query = malloc(1000 * sizeof(char));
      query[0] = '\0';
    }
    strcat(query, and);
    char* greater = "rpg >= ";
    strcat(query, greater);
    char num_min[10];
    sprintf(num_min, "%d", min_ppg);
    strcat(query, num_min);
    strcat(query, and);
    char* less = "rpg <= ";
    strcat(query, less);
    char num_max[10];
    sprintf(num_max, "%d", max_rpg);
    strcat(query, num_max);
  }
  if (use_apg == 1) {
    if (query == NULL) {
      query = malloc(1000 * sizeof(char));
      query[0] = '\0';
    }
    strcat(query, and);
    char* greater = "apg >= ";
    strcat(query, greater);
    char num_min[10];
    sprintf(num_min, "%d", min_apg);
    strcat(query, num_min);
    strcat(query, and);
    char* less = "apg <= ";
    strcat(query, less);
    char num_max[10];
    sprintf(num_max, "%d", max_apg);
    strcat(query, num_max);
  }
  if (use_spg == 1) {
    if (query == NULL) {
      query = malloc(1000 * sizeof(char));
      query[0] = '\0';
    }
    strcat(query, and);
    char* greater = "spg >= ";
    strcat(query, greater);
    char num_min[10];
    sprintf(num_min, "%f", min_spg);
    strcat(query, num_min);
    strcat(query, and);
    char* less = "spg <= ";
    strcat(query, less);
    char num_max[10];
    sprintf(num_max, "%f", max_spg);
    strcat(query, num_max);
  }
  if (use_bpg == 1) {
    if (query == NULL) {
      query = malloc(1000 * sizeof(char));
      query[0] = '\0';
    }
    strcat(query, and);
    char* greater = "bpg >= ";
    strcat(query, greater);
    char num_min[10];
    sprintf(num_min, "%f", min_bpg);
    strcat(query, num_min);
    strcat(query, and);
    char* less = "bpg <= ";
    strcat(query, less);
    char num_max[10];
    sprintf(num_max, "%f", max_bpg);
    strcat(query, num_max);
  }
  if (query == NULL) {
    printf("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG \n");
  } else {
    strcat(query, end);
    if (mysql_query(conn, query)) {
      exit_with_error(conn);
    }
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
      exit_with_error(conn);
    }
    if (mysql_num_rows(result) == 0) {
      printf("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG \n");
    } else {
      int num_fields = mysql_num_fields(result);
      MYSQL_ROW row;
      MYSQL_FIELD* field;
      while (row = mysql_fetch_row(result)) {
	for (int i = 0; i < num_fields; i++) {
	  if (i == 0) {
	    while (field = mysql_fetch_field(result)) {
	      printf("%s ", field->name);
	    }
	    printf("\n");
	  }
	  printf("%s ", row[i] ? row[i] : "NULL");
	}
      }
      printf("\n");
      
    }
    mysql_free_result(result);
  }
  free(query);
}


void query2(MYSQL *conn, char *team_color)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = "';";
  strcat(query, "select TEAM.NAME, COLOR.NAME AS COLOR from TEAM join COLOR using (COLOR_ID) where COLOR.NAME = '");
  strcat(query, team_color);
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  MYSQL_RES* result = mysql_store_result(conn);
  if (result == NULL) {
    exit_with_error(conn);
  }
  if (mysql_num_rows(result) == 0) {
    printf("NAME COLOR\n");
  } else {
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD* field;
    while (row = mysql_fetch_row(result)) {
      for (int i = 0; i < num_fields; i++) {
	if (i == 0) {
	  while (field = mysql_fetch_field(result)) {
	    printf("%s ", field->name);
	  }
	  printf("\n");
	}
	  printf("%s ", row[i] ? row[i] : "NULL");
      }
    }
    printf("\n");
  }
  mysql_free_result(result);
  free(query);
}

void query3(MYSQL *conn, char *team_name)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "select FIRST_NAME, LAST_NAME from PLAYER join TEAM using (TEAM_ID) where TEAM.NAME = '");
  strcat(query, team_name);
  strcat(query, "' order by ppg desc");
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  MYSQL_RES* result = mysql_store_result(conn);
  if (result == NULL) {
    exit_with_error(conn);
  }
  if (mysql_num_rows(result) == 0) {
    printf("FIRST_NAME LAST_NAME\n");
  } else {
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD* field;
    while (row = mysql_fetch_row(result)) {
      for (int i = 0; i < num_fields; i++) {
	if (i == 0) {
	  while (field = mysql_fetch_field(result)) {
	    printf("%s ", field->name);
	  }
	  printf("\n");
	}
	printf("%s ", row[i] ? row[i] : "NULL");
      }
    }
    printf("\n");
  }
  mysql_free_result(result);
  free(query);
}


void query4(MYSQL *conn, char *team_state, char *team_color)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "select FIRST_NAME, LAST_NAME, UNIFORM_NUM from PLAYER, STATE, COLOR, TEAM where PLAYER.TEAM_ID = TEAM.TEAM_ID and TEAM.STATE_ID = STATE.STATE_ID and TEAM.COLOR_ID = COLOR.COLOR_ID and STATE.NAME = '");
  strcat(query, team_state);
  strcat(query, "' and COLOR.NAME = '");
  strcat(query, team_color);
  strcat(query, "'");
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  MYSQL_RES* result = mysql_store_result(conn);
  if (result == NULL) {
    exit_with_error(conn);
  }
  if (mysql_num_rows(result) == 0) {
    printf("FIRST_NAME LAST_NAME UNIFORM_NUM\n");
  } else {
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD* field;
    while (row = mysql_fetch_row(result)) {
      for (int i = 0; i < num_fields; i++) {
	if (i == 0) {
	  while (field = mysql_fetch_field(result)) {
	    printf("%s ", field->name);
	  }
	  printf("\n");
	}
	printf("%s ", row[i] ? row[i] : "NULL");
      }
    }
    printf("\n");
  }
  mysql_free_result(result);
  free(query);
}


void query5(MYSQL *conn, int num_wins)
{
  char* query = NULL;
  query = malloc(1000 * sizeof(char));
  query[0] = '\0';
  char* end = ";";
  strcat(query, "select FIRST_NAME, LAST_NAME, NAME, WINS from PLAYER join TEAM using (TEAM_ID) where WINS > '");
  char wins[10];
  sprintf(wins, "%d", num_wins);
  strcat(query, wins);
  strcat(query, "'");
  strcat(query, end);
  if (mysql_query(conn, query)) {
    exit_with_error(conn);
  }
  MYSQL_RES* result = mysql_store_result(conn);
  if (result == NULL) {
    exit_with_error(conn);
  }
  if (mysql_num_rows(result) == 0) {
    printf("FIRST_NAME LAST_NAME NAME WINS\n");
  } else {
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD* field;
    while (row = mysql_fetch_row(result)) {
      for (int i = 0; i < num_fields; i++) {
	if (i == 0) {
	  while (field = mysql_fetch_field(result)) {
	    printf("%s ", field->name);
	  }
	  printf("\n");
	}
	printf("%s ", row[i] ? row[i] : "NULL");
      }
    }
    printf("\n");
  }
  mysql_free_result(result);
  free(query);
}
