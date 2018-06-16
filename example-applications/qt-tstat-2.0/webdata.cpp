#include "webdata.h"
#include "globalsettings.h"

#include "weatherdata.h"
#include "webdataengine/openweathermapdataengine.h"
#include "webdataengine/wundergrounddataengine.h"

#include "forecastdata.h"

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

#include <QtDebug>
#include <QTime>

/***********************************************************************************************************
* WebData
*   Class that wraps a webdataengine used for retrieving data from an online API. Handles network connection
*   manager and also configures the proxy, first by trying none and then a known one, then failing.
************************************************************************************************************/

WebData::WebData(QObject *parent) :
    QObject(parent)
{
    m_globalSettings = GlobalSettings::getInstance();

    // create network access manager
    manager = new QNetworkAccessManager(this);

    webDataEngine = new OpenWeatherMapDataEngine(manager);
    connect(webDataEngine, SIGNAL(dataAvailable(WeatherData*)), this, SLOT(processDataAvailable(WeatherData*)));
    connect(webDataEngine, SIGNAL(networkTimeout()), this, SLOT(processNetworkTimeout()));

    configureProxy();

}

//FUNCTION: configureProxy()
//
//  configures the correct proxy based on the ProxyState enum defined

void WebData::configureProxy()
{
    if(m_globalSettings->proxyHost() == "" && m_globalSettings->proxyPort() == 0)
        configureNoProxy();
    else
        configureSetProxy();
}

//FUNCTION: configureNoProxy()
//
//  Sets the network access manager to use no proxy at all

void WebData::configureNoProxy()
{
    manager->setProxy(QNetworkProxy(QNetworkProxy::NoProxy));
}


//FUNCTION: configureSetProxy()
//
//  Sets the network access manager to use proxy that is configured in the settings

void WebData::configureSetProxy()
{
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(m_globalSettings->proxyHost());
    proxy.setPort(m_globalSettings->proxyPort());
    manager->setProxy(proxy);
}

//FUNCTION: changeCity()
//
//  Sets the webDataEngine's city variable and then dispatches a request

void WebData::changeCity(QString city)
{
    webDataEngine->setCity(city);
    webDataEngine->dispatchRequest();
}

//FUNCTION: loadLocalData()
//
//  invokes the webdataengine's loadLocalData function to pull locally cached data

void WebData::loadLocalData()
{
    webDataEngine->loadLocalData();
}

//FUNCTION: licenseString()
//
//  Returns the defined license string in the webdataengine

QString WebData::licenseString()
{
    return webDataEngine->licenseString();
}

//FUNCTION: processDataAvailable()
//
//  Catches the dataAvailable signal from the webdataengine and sets the proxy if it worked
//  Otherwise emits signal with either web data or cache data

void WebData::processDataAvailable(WeatherData *weatherData)
{
    if(!weatherData->cachedData())
    {
        m_globalSettings->setProxyInfo(manager->proxy().hostName(), manager->proxy().port());
    }

    emit dataAvailable(weatherData);
}

//FUNCTION: processNetworkTimeout()
//
//  Catches the networkTimeout signal form the webdataengine and tries a new proxy if
//  still in the configuration phase. Other wise emits a normal networkTimeout signal

void WebData::processNetworkTimeout()
{
    emit networkTimeout();
}
