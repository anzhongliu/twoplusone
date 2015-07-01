/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import com.vincent.android.LoginModuleApi;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.test.R;

public class AppActivity extends Cocos2dxActivity {
    private static int flag = 0;
    private static String token;

    private static AppActivity _this;
    public void onCreate(Bundle saveIntanceState) {
        super.onCreate(saveIntanceState);
        _this = this;
        LoginModuleApi.getInstance().setLoginActivityUI(R.layout.login_layout);
    }

    public static void login() {
        LoginModuleApi loginModuleApi = LoginModuleApi.getInstance();
        loginModuleApi.setLoginClass(AppActivity.class);
        loginModuleApi.setLoginRequestCode(1);
        loginModuleApi.login(_this);
    }

//    public static void regist() {
//        LoginModuleApi loginModuleApi = LoginModuleApi.getInstance();
//        loginModuleApi.regist(_this);
//    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (RESULT_OK != resultCode){
            Toast.makeText(this, "内部错误", Toast.LENGTH_LONG).show();
            return;
        }

        int flag = data.getIntExtra("flag", LoginModuleApi.FLAG_ERROR);
        if (flag == LoginModuleApi.FLAG_ERROR) {
            Toast.makeText(this, "注册错误", Toast.LENGTH_LONG).show();
            return ;
        }

        switch(requestCode) {
            case 1: {
                this.token = data.getStringExtra("token");
                if (token == "" || token == null) {
                    Toast.makeText(this, "登陆错误", Toast.LENGTH_LONG).show();
                    return;
                }
                Toast.makeText(this, "登陆成功", Toast.LENGTH_LONG).show();
                break;
            }
        }
    }
}
