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


void ProtocolIAP::restore(ProtocolIAPPurchaseCallback cb){
    _purchaseCallback = cb;
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

void ProtocolIAP::addObserver(){

}
void ProtocolIAP::verifySubscriptionReceipt(const std::string& productID, const std::string& receipt, ProtocolIAPSubscriptionVerifyCallback callback){

}

void ProtocolIAP::payForProduct(TProductInfo info, ProtocolIAPPurchaseCallback cb)
{
    _purchaseCallback = cb;
	payForProduct(info);
}
}} // namespace cocos2d { namespace plugin {
