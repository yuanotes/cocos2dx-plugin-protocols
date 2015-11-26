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
#include "ProtocolIAP.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_IAPWrapper_nativeOnPayResult(JNIEnv*  env, jobject thiz, jstring aliasName, jint ret, jstring msg)
	{
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		std::string strAliasName = PluginJniHelper::jstring2string(aliasName);
		PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strAliasName);
		PluginUtils::outputLog("ProtocolIAP", "nativeOnPayResult(), Get plugin ptr : %p", pPlugin);
		if (pPlugin != NULL)
		{
			PluginUtils::outputLog("ProtocolIAP", "nativeOnPayResult(), Get plugin name : %s", pPlugin->getPluginName());
			ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
            if(pIAP->getPurchaseCallback()){
                pIAP->getPurchaseCallback()((PayResultCode)ret,strMsg);
            } else {
    			PluginUtils::outputLog("ProtocolIAP", "IAP plugin didn't set callback.");
            }
		}
	}
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_IAPWrapper_nativeOnCheckSubscriptionResult(JNIEnv*  env, jobject thiz, jstring aliasName, jint ret, jstring msg)
    {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strAliasName = PluginJniHelper::jstring2string(aliasName);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strAliasName);
        PluginUtils::outputLog("ProtocolIAP", "nativeOnCheckSubscriptionResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolIAP", "nativeOnCheckSubscriptionResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
            if(pIAP->getCheckSubscriptionCallback()){
                pIAP->getCheckSubscriptionCallback()((SubscriptResultCode)ret,strMsg);
            } else {
                PluginUtils::outputLog("ProtocolIAP", "IAP plugin didn't set callback.");
            }
        }
    }
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_IAPWrapper_nativeOnRequestResult(JNIEnv*  env, jobject thiz, jstring aliasName, jint ret, jobject products)
    {
        std::string strAliasName = PluginJniHelper::jstring2string(aliasName);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strAliasName);
        PluginUtils::outputLog("ProtocolIAP", "nativeOnRequestResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolIAP", "nativeOnRequestResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
            if(pIAP->getProductRequestCallback()){
                TProductList result;
                if (products) {
                    // retrieve the java.util.List interface class
                    jclass cList = env->FindClass("java/util/List");

                    // retrieve the size and the get method
                    jmethodID mSize = env->GetMethodID(cList, "size", "()I");
                    jmethodID mGet = env->GetMethodID(cList, "get", "(I)Ljava/lang/Object;");

                    // get the size of the list
                    jint size = env->CallIntMethod(products, mSize);

                    // walk through and fill the vector
                    // for(jint i=0;i<size;i++) {
                    //     jstring strObj = (jstring)env->CallObjectMethod(products, mGet, i);
                    //     const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
                    //     TProductInfo productInfo;
                    //     result.push_back(chr);
                    //     env->ReleaseStringUTFChars(strObj, chr);
                    // }

                    // for(SKProduct *product in products){
                    //     TProductInfo productInfo;
                    //     productInfo["productId"] = product.productIdentifier.UTF8String;
                    //     productInfo["productName"] = product.localizedTitle.UTF8String;
                    //     productInfo["productPrice"] = [NSString stringWithFormat:@"%0.2f", product.price.floatValue].UTF8String;
                    //     productInfo["productDesc"] = product.localizedDescription.UTF8String;
                    //     result.push_back(productInfo);
                    // }
                }
                pIAP->getProductRequestCallback()((IAPProductRequestCode)ret,result);
            } else {
                PluginUtils::outputLog("ProtocolIAP", "IAP plugin didn't set callback.");
            }
        }
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_IAPWrapper_nativeOnRestoreResult(JNIEnv*  env, jobject thiz, jstring aliasName, jint ret, jobject products)
    {
        std::string strAliasName = PluginJniHelper::jstring2string(aliasName);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strAliasName);
        PluginUtils::outputLog("ProtocolIAP", "nativeOnRestoreResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolIAP", "nativeOnRestoreResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
            if(pIAP->getRestoreCallback()){
                TProductIDList result;
                if (products) {
                    // retrieve the java.util.List interface class
                    jclass cList = env->FindClass("java/util/List");

                    // retrieve the size and the get method
                    jmethodID mSize = env->GetMethodID(cList, "size", "()I");
                    jmethodID mGet = env->GetMethodID(cList, "get", "(I)Ljava/lang/Object;");

                    // get the size of the list
                    jint size = env->CallIntMethod(products, mSize);

                    // walk through and fill the vector
                    for(jint i=0;i<size;i++) {
                        jstring strObj = (jstring)env->CallObjectMethod(products, mGet, i);
                        const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
                        result.push_back(chr);
                        env->ReleaseStringUTFChars(strObj, chr);
                    }
                }
                pIAP->getRestoreCallback()((IAPRestoreCode)ret,result);
            } else {
                PluginUtils::outputLog("ProtocolIAP", "IAP plugin didn't set callback.");
            }
        }
    }
}

ProtocolIAP::ProtocolIAP()
{
}

ProtocolIAP::~ProtocolIAP()
{
}

void ProtocolIAP::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolIAP", "The developer info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    	PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "configDeveloperInfo"
    		, "(Ljava/util/Hashtable;)V"))
    	{
        	// generate the hashtable from map
        	jobject obj_Map = PluginUtils::createJavaMapObject(&devInfo);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolIAP::payForProduct(TProductInfo info, ProtocolIAPPurchaseCallback cb)
{
    _purchaseCallback = cb;
	payForProduct(info);
}
void ProtocolIAP::payForProduct(TProductInfo info)
{
    if (info.empty())
    {
        if (_purchaseCallback){
            std::string msg("Product info error");
            _purchaseCallback(kPayFail, msg);
        }
        PluginUtils::outputLog("ProtocolIAP", "The product info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
		PluginJniMethodInfo t;
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "payForProduct"
			, "(Ljava/util/Hashtable;)V"))
		{
			// generate the hashtable from map
			jobject obj_Map = PluginUtils::createJavaMapObject(&info);

			// invoke java method
			t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
			t.env->DeleteLocalRef(obj_Map);
			t.env->DeleteLocalRef(t.classID);
		}
    }
}


void ProtocolIAP::restore(ProtocolIAPRestoreCallback cb){
    setRestoreCallback(cb);
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "restore"
		, "()V"))
	{
		// invoke java method
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolIAP::requestProducts(TProductIDList infoList, ProtocolIAPProductRequestCallback cb){
    if (infoList.empty())
    {
        if (NULL != cb)
        {
            TProductList result;
            cb(kRequestFail, result);
        }
        PluginUtils::outputLog("ProtocolIAP", "The product info is empty!");
        return;
    }
    else
    {
        setProductRequestCallback(cb);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    	PluginJniMethodInfo t;
    	if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "requestProducts"
    		, "(Ljava/util/ArrayList;)V"))
    	{
    		// invoke java method
            jobject obj_Array = PluginUtils::createArrayFromVector(&infoList);
    		t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Array);
            t.env->DeleteLocalRef(obj_Array);
    		t.env->DeleteLocalRef(t.classID);
    	}
    }
}
void ProtocolIAP::purchaseSubscription(TProductInfo info,ProtocolIAPCheckSubscriptionCallback callback) {
    if (info.empty())
    {
        if (NULL != callback)
        {
            std::string stdstr("Product info error");
            callback(kSubscriptionVerifyFailed,stdstr);
        }
        PluginUtils::outputLog("ProtocolIAP", "The product info is empty!");
        return;
    }
    else
    {
        setCheckSubscriptionCallback(callback);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , "purchaseSubscription"
            , "(Ljava/util/Hashtable;)V"))
        {
            // generate the hashtable from map
            jobject obj_Map = PluginUtils::createJavaMapObject(&info);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolIAP::checkSubscription(TProductInfo info, ProtocolIAPCheckSubscriptionCallback cb){
    if (info.empty())
    {
        if (NULL != cb)
        {
            std::string stdstr("Product info error");
            cb(kSubscriptionVerifyFailed,stdstr);
        }
        PluginUtils::outputLog("ProtocolIAP", "The product info is empty!");
        return;
    }
    else
    {
        setCheckSubscriptionCallback(cb);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , "checkSubscription"
            , "(Ljava/util/Hashtable;)V"))
        {
            // generate the hashtable from map
            jobject obj_Map = PluginUtils::createJavaMapObject(&info);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}




}} // namespace cocos2d { namespace plugin {
