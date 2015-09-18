#ifndef I_APPLICATION_PREFERENCES_H
#define I_APPLICATION_PREFERENCES_H

class QString;

class IApplicationPreferences {
public:
    virtual ~IApplicationPreferences() { }

    virtual QString app_name() const = 0;
    virtual QString version() const = 0;
};

#endif
