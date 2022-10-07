#ifndef QMOSQUITTO_H
#define QMOSQUITTO_H

//#include <QtQuick/QQuickPaintedItem>
#include <QtQuick/qquickitem.h>
#include "mosquitto/include/mosquitto.h"

class Mosquitto : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost REQUIRED)
    Q_PROPERTY(int port READ port WRITE setPort REQUIRED)
    Q_PROPERTY(QStringList subscribe READ subscribe WRITE setSubscribe)
    QML_NAMED_ELEMENT(Mosquitto)
public:
    explicit Mosquitto(QQuickItem *parent = nullptr);
    ~Mosquitto() override;

signals:
    void connected();
    void newMessage(QString topic,QString message);

public slots:
    bool connectToBroker();
    void disconnectBroker();

    void setSubscribe(QStringList);
    QStringList subscribe();

    void setHost(QString);
    QString host();

    void setPort(int);
    int port();

    void setUsername(QString);
    QString username();

    void setPassword(QString);
    QString password();

private:
    static void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) ;
    static void connect_callback(struct mosquitto *mosq, void *userdata, int result);
    static void subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);
    static void log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str);

private:
    QString _host;
    int _port;
    QString _username;
    QString _password;
    QStringList _subscribe;
    mosquitto *_mosq;

};

#endif // QMOSQUITTO_H
