/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CCX_PROTOCOL_IAP_H__
#define __CCX_PROTOCOL_IAP_H__

#include "PluginProtocol.h"
#include <map>
#include <string>
#include <functional>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TIAPDeveloperInfo;
typedef std::map<std::string, std::string> TProductInfo;
typedef std::vector<std::string> TProductIDList;
typedef std::vector<TProductInfo> TProductList;
typedef enum
{
    kPaySuccess = 0,
    kPayFail,
} PayResultCode;

typedef enum
{
    kSubscriptionVerifySuccess = 0,
    kSubscriptionVerifyFailed,
} SubscriptResultCode;



typedef enum {
    kRequestSuccees=0,
    kRequestFail,
    kRequestTimeout,
} IAPProductRequestCode;

typedef enum {
    kRestored = 0,
    kRestoreFailed,
} IAPRestoreCode;

class ProtocolIAP : public PluginProtocol
{
public:
	ProtocolIAP();
	virtual ~ProtocolIAP();

	typedef std::function<void(PayResultCode, std::string&)> ProtocolIAPPurchaseCallback;
	typedef std::function<void(SubscriptResultCode, std::string&)> ProtocolIAPCheckSubscriptionCallback;
    typedef std::function<void(IAPProductRequestCode, TProductList)> ProtocolIAPProductRequestCallback;
    typedef std::function<void(IAPRestoreCode, TProductIDList)> ProtocolIAPRestoreCallback;


    /**
    @brief config the developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TIAPDeveloperInfo devInfo);

    /**
    @brief pay for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
    @warning For different plugin, the parameter should have other keys to pay.
             Look at the manual of plugins.
    */
    void payForProduct(TProductInfo info);
    void payForProduct(TProductInfo info, ProtocolIAPPurchaseCallback cb);
    void requestProducts(TProductIDList infoList, ProtocolIAPProductRequestCallback cb);
    void restore(ProtocolIAPRestoreCallback cb);
    void checkSubscription(TProductInfo info, ProtocolIAPCheckSubscriptionCallback cb);
    void purchaseSubscription(TProductInfo info, ProtocolIAPCheckSubscriptionCallback cb);

    /**
    @brief set callback function
    */
    inline void setPurchaseCallback(ProtocolIAPPurchaseCallback &cb)
    {
    	_purchaseCallback = cb;
    }

    /**
    @brief get callback function
    */
    inline ProtocolIAPPurchaseCallback getPurchaseCallback()
    {
    	return _purchaseCallback;
    }

    inline void setCheckSubscriptionCallback(ProtocolIAPCheckSubscriptionCallback & cb){
        _checkSubscriptionCallback = cb;
    }

    inline ProtocolIAPCheckSubscriptionCallback getCheckSubscriptionCallback(){
        return _checkSubscriptionCallback;
    }

    inline void setProductRequestCallback(ProtocolIAPProductRequestCallback & cb){
        _productRequestsCallback = cb;
    }

    inline ProtocolIAPProductRequestCallback getProductRequestCallback(){
        return _productRequestsCallback;
    }

    inline void setRestoreCallback(ProtocolIAPRestoreCallback & cb){
        _restoreCallback = cb;
    }

    inline ProtocolIAPRestoreCallback getRestoreCallback(){
        return _restoreCallback;
    }
protected:
    ProtocolIAPPurchaseCallback _purchaseCallback;
    ProtocolIAPCheckSubscriptionCallback _checkSubscriptionCallback;
    ProtocolIAPProductRequestCallback _productRequestsCallback;
    ProtocolIAPRestoreCallback _restoreCallback;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_IAP_H__ */
