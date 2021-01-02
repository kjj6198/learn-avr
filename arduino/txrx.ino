
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available())
  {
    String str = Serial.readString();
    Serial.println(str);
  }
}