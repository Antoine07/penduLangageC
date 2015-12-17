
typedef struct _tab_score
{
    int score;
    char * username;
} tab_score;

// connexion database
void db_create(const char *db_filename)
{
    sqlite3 *db;
    char *message_erreur = 0;
    int rc;
    char *sql;

    rc = sqlite3_open(db_filename, &db);

    if( rc ){
        fprintf(stderr,
                "Ouverture de la base de données %s impossible: %s\n",
                db_filename,
                sqlite3_errmsg(db));
        exit(1);
    }

    sql = "CREATE TABLE scores("  \
          "username TEXT    NOT NULL," \
          "score INTEGER NOT NULL);";

    rc = sqlite3_exec(db, sql, NULL, 0, &message_erreur);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la création de la base de donnée %s: %s\n",
                db_filename,
                message_erreur);
        sqlite3_free(message_erreur);
    }

    sqlite3_close(db);

    return;
}


void db_set(const char *db_filename, tab_score s){

	 sqlite3 *db;
    int rc;
    static char *base_sql = "INSERT INTO scores (username, score) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_open(db_filename, &db);

    if( rc ){
        fprintf(stderr,
                "Ouverture de la base de données %s impossible: %s\n",
                db_filename,
                sqlite3_errmsg(db));
        exit(1);
    }

    // Préparation de la requête.
    rc = sqlite3_prepare(db, base_sql, -1, &stmt, 0);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la préparation de la requête SQL %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
        exit(1);
    }

    // Bind des paramètres
    rc = sqlite3_bind_text(stmt, 1, s.username, strlen(s.username), SQLITE_STATIC);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors du bind de %s à la requête %s pour la base de donnéee %s:\n",
                s.username,
                base_sql,
                db_filename);
        exit(1);
    }

    rc = sqlite3_bind_int(stmt, 2, s.score);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors du bind de %d à la requête %s pour la base de donnéee %s:\n",
                s.score,
                base_sql,
                db_filename);
        exit(1);
    }

    // Exécution de la requête
    while (1)
    {
        rc = sqlite3_step(stmt);
        if( rc == SQLITE_DONE )
        {
            break;
        }
        else
        {
            fprintf(stderr,
                "Problème lors de la suppression des données de requête %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
            exit(1);
        }
    }

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

}


tab_score* db_get(const char *db_filename, char *username)
{
    sqlite3 *db;
    int rc;
    static char *base_sql = "SELECT username, score FROM scores WHERE username = ?;";
    sqlite3_stmt *stmt;
    tab_score * res;

    res = malloc(sizeof(tab_score));
    res->username = NULL;
    res->score = 0;

    rc = sqlite3_open(db_filename, &db);

    if( rc ){
        fprintf(stderr,
                "Ouverture de la base de données %s impossible: %s\n",
                db_filename,
                sqlite3_errmsg(db));
        exit(1);
    }

    // Préparation de la requête.
    rc = sqlite3_prepare(db, base_sql, -1, &stmt, 0);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la préparation de la requête SQL %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
        exit(1);
    }

    // Bind des paramètres
    rc = sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors du bind de %s à la requête %s pour la base de donnéee %s:\n",
                username,
                base_sql,
                db_filename);
        exit(1);
    }

    // Exécution de la requête
    while (1)
    {
        rc = sqlite3_step(stmt);
        if( rc == SQLITE_DONE )
        {
            break;
        }
        else if( rc == SQLITE_ROW )
        {
            const char *username;
            int score;

            username  = (const char *)sqlite3_column_text (stmt, 0);
            score = sqlite3_column_int(stmt, 1);

            res->username = malloc(sizeof(char) * (strlen(username) + 1));
           	strcpy(res->username, username);
    		res->score = score;

        }
        else
        {
            fprintf(stderr,
                "Problème lors de la lecture des données de requête %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
            exit(1);
        }
    }

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return res;
}