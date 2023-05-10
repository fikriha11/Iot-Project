void Lubangi(int x, int y, int l) {
  int sleep = 500;
  gotoY(y);
  delay(sleep);
  gotoX(x);
  delay(sleep);
  gotoZ(300);
  delay(sleep);
  gotoL(l);
}

void taruhBibit(int x, int y, int l) {
  int sleep = 500;
  gotoY(y);
  delay(sleep);
  gotoX(x);
  delay(sleep);
  gotoZ(150);
  delay(sleep);
  gotoL(l);
}

void taruhPipa(int x, int y) {
  homeL(); delay(500);
  gotoZ(-175); delay(500);
  gotoX(x); delay(500);
  homeY(); delay(500);
  servobukatitik(); delay(3000);
  homeZ(); delay(500);
  servotutup(); delay(2000);
}

void ambilTanaman(int x) {
  int sleep = 500;
  gotoX(x);
  servobukatitik(); delay(1000);
  homeY(); delay(1000);
  gotoZ(95); delay(1000);
  servotutup(); delay(2000);
}

void DiTanam(int x, int y, int l, int pos) {
  homie();
  delay(500);
  Lubangi(x, y, l);
  delay(500);
  homie();
  delay(500);
  ambilTanaman(pos);
  delay(500);
  taruhBibit(x - pos, y, l / 2);  // Put Tanaman
  taruhPipa(-(x - pos), -(y));
  delay(500);
  homie();
}

void Tanam() {
  switch (Count) {
    case 1 :
      DiTanam(47,  140, 13, 2);
      Count = 0;
      break;
    case 2 :
      DiTanam(125, 140, 13, 21);
      Count = 0;
      break;
    case 3 :
      DiTanam(203, 140, 13, 38);
      Count = 0;
      break;
    case 4 :
      DiTanam(281, 140, 13, 55);
      Count = 0;
      break;

    case 5 :
      DiTanam(47,  235, 13, 73);
      Count = 0;
      break;
    case 6 :
      DiTanam(125, 235, 13, 91);
      Count = 0;
      break;
    case 7 :
      DiTanam(203,  235, 13, 109);
      Count = 0;
      break;
    case 8 :
      DiTanam(281, 235, 13, 126);
      Count = 0;
      break;

    case 9 :
      DiTanam(47,  320, 13, 143);
      Count = 0;
      break;
    case 10 :
      DiTanam(125, 320, 13, 161);
      Count = 0;
      break;
    case 11 :
      DiTanam(203,  320, 13, 179);
      Count = 0;
      break;
    case 12 :
      DiTanam(281, 320, 13, 196);
      Count = 0;
      break;

    case 13 :
      DiTanam(47,  410, 13, 214);
      Count = 0;
      break;
    case 14 :
      DiTanam(125, 410, 13, 231);
      Count = 0;
      break;
    case 15 :
      DiTanam(203,  410, 13, 248);
      Count = 0;
      break;
    case 16 :
      DiTanam(281, 410, 13, 266);
      Count = 0;
      break;

    case 17 :
      DiTanam(47,  490, 13, 284);
      Count = 0;
      break;
    case 18 :
      DiTanam(125, 490, 13, 301);
      Count = 0;
      break;
    case 19 :
      DiTanam(203,  490, 13, 318);
      Count = 0;
      break;
    case 20 :
      DiTanam(281, 490, 13, 336);
      Count = 0;
      break;

    default :
      break;
  }
}
