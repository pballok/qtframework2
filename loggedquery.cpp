#include <QSqlError>

#include "loggedquery.h"
#include "tracer.h"

bool LoggedQuery::exec(const QString &query) {
    TRACE_ME(query.toStdString());

    auto result = QSqlQuery::exec(query);
    if(result) {
        if(isSelect()) {
            TRACE_RESULT(QString("Query returned %1 rows").arg(size()).toStdString());
        } else {
            TRACE_RESULT(QString("Query affected %1 rows").arg(numRowsAffected()).toStdString());
        }
    } else {
        LOG(ERROR) << "Database error: " << lastError().text().toStdString();
        TRACE_RESULT("ERROR");
    }

    return result;
}
