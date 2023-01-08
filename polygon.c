#include<stdio.h>
#include<handy.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define X_ORIGIN 250
#define Y_ORIGIN 250
#define RADIUS_ORIGIN 200

int windowId;

//数字を入力する関数
double enter_num(int text_x , int text_y , int width , int layer_id){
    int i,j;
    float num;
    int start_x = text_x;
    char text_key[5]="";
    char key[2]="";

    HgSetFont(HG_T,50);
    HgText(0,225,"正      角形を作図する");
    
    i=0;
    HgWSetFont(layer_id,HG_T,25);
    for (;;) {
        
        key[0] = HgGetChar();
        if((key[0]>='0' && key[0]<='9') || (key[0] == '.')){ //数字のみの入力を受け付ける

            if(text_x +10 < start_x + width){ //枠からはみ出なければ
                text_key[i] = key[0];
                
                HgWText(layer_id,text_x,text_y,&text_key[i]);
                text_x+=20;
                i++;
            }

        }else if(key[0] == '\x7f'){ //DELETEキーを押したとき
            HgLClear(layer_id);
            text_x = start_x;

            for(j=0; j<i; j++){
                text_key[j] ='\0';
            }
            i=0;
        }else if(key[0] == '\x0d'){ //ENTERキーを押したとき
            break;
        }
    }
    HgClear();

    num = atof(text_key);   

    return num;
}

void drowText(double polygonNum){
    int interiorAngle = 180 - 360 / polygonNum;
    HgSetFont(HG_M,20);
    HgText(25,450,"正%g角形",polygonNum);
    HgText(25,425,"内角:");
    HgText(75,425,"%d°",interiorAngle);
}

void polygonAnime(double polygonNum){
    double x[200],y[200],newX[200],newY[200],polygonTheta,rotateTheta,theta;
    int i,layer,startLayer;

    polygonTheta = (2.0 * M_PI) / polygonNum;
    theta = polygonTheta;
    x[0] = X_ORIGIN + RADIUS_ORIGIN * cos(0);
    y[0] = Y_ORIGIN + RADIUS_ORIGIN * sin(0);

    i=1;
    startLayer = HgWAddLayer(windowId);
    for(;;){
        x[i] = X_ORIGIN + RADIUS_ORIGIN * cos(theta);
        y[i] = Y_ORIGIN + RADIUS_ORIGIN * sin(theta);
        HgWLine(startLayer,x[i-1],y[i-1],x[i],y[i]);

        if(fmod(theta,(2.0 * M_PI)) <= 0.01) break;

        i++;
        theta += polygonTheta;
    }

    HgWText(startLayer,320,10,"ENTERキーで回転");
    for(;;){
        int key = HgGetChar();
        if(key == '\x0d') break;
    }

    HgLClear(startLayer);

    HgWText(startLayer,10,10,"円を表示させる→Yキー 表示させない→Nキー");
    for(;;){
        int key = HgGetChar();

        if(key == 'y'){
            HgCircle(X_ORIGIN,Y_ORIGIN,RADIUS_ORIGIN);
            break;
        }
        if(key == 'n') break;
    }
    
    HgLClear(startLayer);

    doubleLayer layers;
    layers = HgWAddDoubleLayer(windowId);

    rotateTheta = M_PI / 120.0;
    for(;;){
        layer = HgLSwitch(&layers);  
        HgLClear(layer); 

        newX[0] = (x[0] - X_ORIGIN) * cos(rotateTheta) - (y[0] - Y_ORIGIN) * sin(rotateTheta) +X_ORIGIN;
        newY[0] = (x[0] - X_ORIGIN) * sin(rotateTheta) + (y[0] - Y_ORIGIN) * cos(rotateTheta) +Y_ORIGIN;

        for(int j = 1; j <= i; j++){
            newX[j] = (x[j] - X_ORIGIN) * cos(rotateTheta) - (y[j] - Y_ORIGIN) * sin(rotateTheta) +X_ORIGIN;
            newY[j] = (x[j] - X_ORIGIN) * sin(rotateTheta) + (y[j] - Y_ORIGIN) * cos(rotateTheta) +Y_ORIGIN;
            HgWLine(layer,newX[j-1],newY[j-1],newX[j],newY[j]);
        }
        HgSleep(1.0 / 30.0);
        

        layer = HgLSwitch(&layers);  
        HgLClear(layer); 

        x[0] = (newX[0] - X_ORIGIN) * cos(rotateTheta) - (newY[0] - Y_ORIGIN) * sin(rotateTheta) +X_ORIGIN;
        y[0] = (newX[0] - X_ORIGIN) * sin(rotateTheta) + (newY[0] - Y_ORIGIN) * cos(rotateTheta) +Y_ORIGIN;

        for(int j = 1; j <= i; j++){

            x[j] = (newX[j] - X_ORIGIN) * cos(rotateTheta) - (newY[j] - Y_ORIGIN) * sin(rotateTheta) +X_ORIGIN;
            y[j] = (newX[j] - X_ORIGIN) * sin(rotateTheta) + (newY[j] - Y_ORIGIN) * cos(rotateTheta) +Y_ORIGIN;
            HgWLine(layer,x[j-1],y[j-1],x[j],y[j]);
        }
        HgSleep(1.0 / 30.0);
    
    }

}

int main(){
    float polygonNum;
    int switchLayer;
    windowId = HgOpen(500,500);
    switchLayer = HgWAddLayer(windowId);
    polygonNum = enter_num(50,240,75,switchLayer);
    drowText(polygonNum);
    polygonAnime(polygonNum);
    HgGetChar();
    HgClose();

    return 0;
}
