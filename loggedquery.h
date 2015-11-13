#ifndef LOGGEDQUERY_H
#define LOGGEDQUERY_H

#include <QSqlQuery>

class LoggedQuery : public QSqlQuery {
public:
    explicit LoggedQuery(QSqlDatabase db) : QSqlQuery(db) { }
    bool exec(const QString& query);
};

#endif
