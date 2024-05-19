#include <math.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
float x;
float y;
float l1 = 14;
float l2 = 14;
float theta1, theta2;

void setup() {
  Serial.begin(9600);
  servo1.attach(6);
  servo2.attach(9);
  Serial.println("Begin:");
}

float tinhTheta2 (float x, float y)
{
  theta2 = (acos((x*x + y*y- l1 * l1 - l2 * l2) / (2 * l1 * l2)));
  return theta2;
}

float tinhTheta1(float x, float y, float theta2)
{
    return (atan2(y,x) + atan2(l2 * sin(theta2), l1 + l2 * cos(theta2)));
}

void diChuyenNgang(float x0, float y0, float x1, float y1)
{
  while (x0 != x1)
  {
    theta2 = tinhTheta2(x0, y0);

    theta1 = tinhTheta1(x0, y0, theta2);
    
    if (x0 > x1)
    {
        x0 -= 0.5;
    }
    
    if (x0 < x1)
    {
        x0 += 0.5;
    }
    

  Serial.print("Goc1: ");
  Serial.println(round(theta1*(180/PI)));

  servo1.write(round(theta1*(180/PI))); 

  Serial.print("Goc2: ");
  Serial.println(round(theta2*(180/PI)));

  servo2.write(round(theta2*(180/PI))+90); 

  delay(100);
  }
}

void diChuyenDoc(float x0, float y0, float x1, float y1)
{
    while (y0 != y1)
  {
    theta2 = tinhTheta2(x0, y0);

    theta1 = tinhTheta1(x0, y0, theta2);

    if (y0 > y1)
    {
        y0 -= 0.5;
    }
    
    if (y0 < y1)
    {
        y0 += 0.5;
    }
    
  Serial.print("Goc1: ");
  Serial.println(round(theta1*(180/PI)));

  servo1.write(round(theta1*(180/PI))); 

  Serial.print("Goc2: ");
  Serial.println(round(theta2*(180/PI)));

  servo2.write(round(theta2*(180/PI)) + 90); 

  delay(100);
  }
}

void diChuyenCheo(float x0, float y0, float x1, float y1) {
  float deltaX = x1 - x0; // Độ chênh lệch giữa tọa độ X của hai điểm
  float deltaY = y1 - y0; // Độ chênh lệch giữa tọa độ Y của hai điểm
  float step = 0.5; // Bước nhảy

  // Tính góc của đường chéo
  float angle = atan2(deltaY, deltaX);

  for (int i = 0 ; i < 14 ; i++)
  { 
    // Tính toán tọa độ mới dựa trên bước nhảy và góc của đường chéo
    x0 += cos(angle) * step;
    y0 += sin(angle) * step;

    theta2 = tinhTheta2(x0, y0);

    theta1 = tinhTheta1(x0, y0, theta2);

    servo1.write(round(theta1 * (180 / PI)));
    servo2.write(round(theta2 * (180 / PI)) + 90);

    // Đợi một khoảng thời gian trước khi di chuyển đến vị trí tiếp theo
    delay(100);
  }
}


void loop() {
  
  //ve hinh chu nhat
  diChuyenNgang(5, 19, 12, 19);
  diChuyenDoc(12, 19, 12, 23);
  diChuyenNgang(12, 23, 5, 23);
  diChuyenDoc(5, 23 , 5, 19);
  diChuyenCheo(5, 19, 12, 23);
  diChuyenDoc(12, 23 , 12, 19);
  diChuyenCheo(12, 19, 5, 23);
  diChuyenDoc(5, 23 , 5, 19);

  delay(1000);
  
}
