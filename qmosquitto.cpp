#include "qmosquitto.h"
#include "include/mosquitto.h"

#include <QPainter>

Mosquitto::Mosquitto(QQuickItem *parent)
    : QObject(parent)
{
    mosquitto_lib_init();
    _mosq = nullptr;
}

Mosquitto::~Mosquitto()
{
}

bool Mosquitto::connectToBroker()
{
    bool ret = false;
    if(_mosq != nullptr)
        return ret;

    _mosq = mosquitto_new(NULL, true, this);
    mosquitto_log_callback_set(_mosq,log_callback);
    mosquitto_connect_callback_set(_mosq,connect_callback);
    mosquitto_message_callback_set(_mosq,message_callback);
    mosquitto_subscribe_callback_set(_mosq,subscribe_callback);
    if(mosquitto_connect(_mosq , _host.toStdString().c_str(),_port, 60)){
        fprintf(stderr, "Unable to connect.\n");
    }
    else
        ret = true;
    mosquitto_loop_start(_mosq);
    if(ret)
        qDebug() << " mosquitto connected to broker";
    return ret;
}

void Mosquitto::disconnectBroker()
{
    mosquitto_destroy(_mosq);
}

void Mosquitto::setSubscribe(QStringList val)
{
    _subscribe = val;
}

QStringList Mosquitto::subscribe()
{
    return _subscribe;
}

void Mosquitto::setHost(QString val)
{
    _host = val;
}

QString Mosquitto::host()
{
    return _host;
}

void Mosquitto::setPort(int val)
{
    _port = val;
}

int Mosquitto::port()
{
    return _port;
}

void Mosquitto::setUsername(QString val)
{
    _username = val;
}

QString Mosquitto::username()
{
    return _username;
}

void Mosquitto::setPassword(QString val)
{
    _password = val;
}

QString Mosquitto::password()
{
    return _password;
}

void Mosquitto::message_callback(mosquitto *mosq, void *userdata, const mosquitto_message *message)
{
    emit ((Mosquitto*)userdata)->newMessage(QString(message->topic),QString((char*)message->payload));
}

void Mosquitto::connect_callback(mosquitto *mosq, void *userdata, int result)
{
    if(!result){
        foreach (QString topic,((Mosquitto*)userdata)->_subscribe) {
            mosquitto_subscribe(mosq, NULL, topic.toStdString().c_str(), 2);
        }
    }else{
        fprintf(stderr, "Connect failed\n");
    }
}

void Mosquitto::subscribe_callback(mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{

}

void Mosquitto::log_callback(mosquitto *mosq, void *userdata, int level, const char *str)
{

}
