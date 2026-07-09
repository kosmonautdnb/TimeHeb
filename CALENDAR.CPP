// All calculations and Statements may be wrong in this onverter.
// It's just a fast hack to preserve somehow that stuff from my Kabbalah Centre past.
// Some additions or changes are made by me.
#include "DOS.HPP"
#include "GL.H"
#include "IMGUIGL.HPP"
#include "IMGUI.H"
#include <stdio.h>
#include <conio.h>
#include <math.h>

const char *monthsH[13] = {
  "Tischrei",
  "Cheshwan",
  "Kislev",
  "Tewet",
  "Schwat",
  "Adar",
  "Adar II",
  "Nissan",
  "Ijar",
  "Sivan",
  "Tammus",
  "Av",
  "Elul"
};

const char *monthsHZ[13] = {
  "Waage",
  "Scorpion",
  "Schuetze",
  "Steinbock",
  "Wassermann",
  "Fische",
  "Fische",
  "Widder",
  "Stier",
  "Zwillinge",
  "Krebs",
  "Loewe",
  "Jungfrau"
};

const char *monthsG[12] = {
  "Januar",
  "Februar",
  "Maerz",
  "April",
  "Mai",
  "Juni",
  "Juli",
  "August",
  "September",
  "Oktober",
  "November",
  "Dezember"
};

const char *days[7] = {
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

const char *sephiras[11] = {
  "Keter(Krone)",
  "Chochmah(Weisheit)",
  "Binah(Understanding)",
  "Daat(Abgrund)",
  "Chesed(Gnade)",
  "Gevurah(Strenge)",
  "Tiferet(Schoenheit)",
  "Nezach(Ausdauer/Sieg)",
  "Hod(Demut/Stolz)",
  "Yesod(Rausch)", // actually fundament
  "Malchut(Koenigreich)"
};

const char *parashats[54+9] = {
  "Bereshit", // 0
  "Noach", // 1
  "Lech Lecha", // 2
  "Vayera", // 3
  "Chayei Sarah", // 4
  "Toldot", // 5
  "Vayetze", // 6
  "Vayishlach", // 7
  "Vayeshev", // 8
  "Mikets", // 9
  "Vayigash", // 10
  "Vayechi", // 11
  "Shemot", // 12
  "Vaeira", // 13
  "Bo", // 14
  "Beschalach", // 15
  "Yitro", // 16
  "Mishpatim", // 17
  "Terumah", // 18
  "Tetzaveh", // 19
  "Ki Tisa", // 20
  "Vayakhel", // 21
  "Pekudei", // 22
  "Vayikra", // 23
  "Tzav", // 24
  "Shemini", // 25
  "Tazria", // 26
  "Metzora", // 27
  "Acharei Mot", // 28
  "Kedoshim", // 29
  "Emor", // 30
  "Behar", // 31
  "Bechukotai", // 32
  "Bamidbar", // 33
  "Naso", // 34
  "Behalotecha", // 35
  "Shelach", // 36
  "Korach", // 37
  "Chukat", // 38
  "Balak", // 39
  "Pinchas", // 40
  "Matot", // 41
  "Masei", // 42
  "Devarim", // 43
  "Vaetchanan", // 44
  "Ekev", // 45
  "Re'Eh", // 46
  "Shoftim", // 47
  "Ki Tetze", // 48
  "Ki Tavo", // 49
  "Nitzavim", // 50
  "Vayelech", // 51
  "Ha'Azinu", // 52
  "V'Zot Habrachah", // 53
  //
#define VAYEKHEL 21
#define TAZRIA 26
#define ACHAREIMOT 28
#define BEHAR 31
#define CHUKAT 38
#define MATOT 41
#define NITZAVIM 50
#define VAYEKHEL_PEKUDEI 54
#define TAZRIA_METZORA 55
#define ACHAREIMOT_KEDOSHIM 56
#define BEHAR_BECHUKOTEI 57
#define CHUKAT_BALAK 58
#define MATOT_MASEI 59
#define NITZAVIM_VAYELECH 60
#define EMPTY 61
#define DIDNTCALC 62
  "Vayekhel+Pekudei",
  "Tazria+Metzora",
  "Acharaei Mot+Kedoshim",
  "Behar+Bechukotai",
  "Chukat+Balak",
  "Matot+Masei",
  "Nitzavim+Vayelech",
  "Empty",
  "Other year end"
};

const char *parashatContents[54+9] = {
  "Genesis. Starting with a beth, Yin Yang, Gott sleeps, Adam and Chava, Kain and Abel, erly generations", // 0
  "Genesis. Arche, Babel", // 1
  "Genesis. Abraham, Lot", // 2
  "Genesis. Abraham visitors, Sodom Gomorrah, Isaac und Hagar, Isaac binding", // 3
  "Genesis. Tot von Sarah (Machpela), Isaaks junge Frau, Abrahams tot, Ismaels nachkommen.", // 4
  "Genesis. Geburt Jakob Esau, Jakobs Suppe, Taeuschung Isaacs, Jakob flieht", // 5
  "Genesis. Jakobs Engelleiter, Laban und Leah und Rahel, Jakobs Flucht", // 6
  "Genesis. Jakon kaempft mit Engel, Esau wiedersehen, Dina entfuehrung, Rahels Tod", // 7
  "Genesis. Josephs dreams, Joseph nach Aegypten, Tamar, Potiphars wife, Joseph Gefaengnis", // 8
  "Genesis. Pharaos dreams, Joseph wird bekannt, Josephs Brueder", // 9
  "Genesis. Judahs Bitte, Joseph zeigt sich, Jakob zieht nach Aegypten, Goschen", // 10
  "Genesis. Jakobs letzter Wunsch, Segnung der zwei Brueder und der 12 Soehne, Jakobs Tot, Josephs Tot.", // 11
  "Shemot", // 12
  "Vaeira", // 13
  "Bo", // 14
  "Beschalach", // 15
  "Yitro", // 16
  "Mishpatim", // 17
  "Terumah", // 18
  "Tetzaveh", // 19
  "Ki Tisa", // 20
  "Vayakhel", // 21
  "Pekudei", // 22
  "Vayikra", // 23
  "Tzav", // 24
  "Shemini", // 25
  "Tazria", // 26
  "Metzora", // 27
  "Acharei Mot", // 28
  "Kedoshim", // 29
  "Emor", // 30
  "Behar", // 31
  "Bechukotai", // 32
  "Bamidbar", // 33
  "Naso", // 34
  "Behalotecha", // 35
  "Shelach", // 36
  "Korach", // 37
  "Chukat", // 38
  "Balak", // 39
  "Pinchas", // 40
  "Matot", // 41
  "Masei", // 42
  "Devarim", // 43
  "Vaetchanan", // 44
  "Ekev", // 45
  "Re'Eh", // 46
  "Shoftim", // 47
  "Ki Tetze", // 48
  "Ki Tavo", // 49
  "Nitzavim", // 50
  "Vayelech", // 51
  "Ha'Azinu", // 52
  "V'Zot Habrachah", // 53
  //
#define VAYEKHEL 21
#define TAZRIA 26
#define ACHAREIMOT 28
#define BEHAR 31
#define CHUKAT 38
#define MATOT 41
#define NITZAVIM 50
#define VAYEKHEL_PEKUDEI 54
#define TAZRIA_METZORA 55
#define ACHAREIMOT_KEDOSHIM 56
#define BEHAR_BECHUKOTEI 57
#define CHUKAT_BALAK 58
#define MATOT_MASEI 59
#define NITZAVIM_VAYELECH 60
#define EMPTY 61
#define DIDNTCALC 62
  "Vayekhel+Pekudei",
  "Tazria+Metzora",
  "Acharaei Mot+Kedoshim",
  "Behar+Bechukotai",
  "Chukat+Balak",
  "Matot+Masei",
  "Nitzavim+Vayelech",
  "Empty",
  "Other year end"
};

int parashatPerShabbat[70] = {0};

unsigned int continuosFromGregorian(int day, int month, int year) {
  int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if ((year & 3) == 0) months[1] = 29;
  unsigned int ret = 0;
  ret += 365 * year;
  ret += (year+3) / 4;
  ret += day-1;
  for (int i = 0; i < (month-1); i++) {
    ret += months[i % 12];
  }
  return ret + 7 - 3; // monday is 0
}

void gregorianFromContinuos(unsigned int continuos, int &day, int &month, int &year) {
  continuos -= 7-3; // monday is 0
  year = 0;
  while(1==1) {
    if ((year & 3) ==  0) {
      if (continuos < 366) break;
      continuos-=366; 
    } else  {
      if (continuos < 365) break;
      continuos-=365;
    }
    year++;
  }
  int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if ((year & 3) == 0) months[1] = 29;
  month = 0;
  int a = continuos;
  for (int i = 0; i < a; i++) {
    if (continuos >= months[month % 12]) {
      continuos -= months[month % 12];
      month++;
    }
  }
  month = month % 12;
  month += 1;
  day = continuos + 1;
}

bool hebrewLeapYear(int year) {
  return (((7*year)+1) % 19)<7;
}

// seems to be not 100% correct with very old dates maybe the problem is the missing int64(doesn't seem so) (or in my gregorian stuff)
// hebcal also says before around 1800 there are problems
int daysForHebrewYear(int year) {
  // I understand nothing of this function (it's soft copied from hebcal)
  int prev = year - 1;
  int m_elapsed = 235*(prev/19)+12*(prev%19)+(((prev%19)*7+1)/19);
  int p_elapsed = 204+793*(m_elapsed%1080);
  int h_elapsed = 5 + 12*m_elapsed + 793*(m_elapsed/1080)+(p_elapsed/1080);
  int parts = (p_elapsed % 1080) + 1080 * (h_elapsed % 24);
  int day = 1 + 29 * m_elapsed + (h_elapsed / 24);
  if (parts >= 19440 ||
      ( (day % 7)==2 && (parts >= 9924) && (!hebrewLeapYear(year))) ||
      ( (day % 7)==1 && (parts >= 16789) && hebrewLeapYear(prev))
     ) {
    day++;
  }
  if ( ((day % 7)==0) || ((day % 7)==3) || ((day%7)==5)) {
    day++;
  }
  return day;
}
                                                             
int hebrewStartYear = 0;
int gregorianStartYear = 0;
int yearCount = 0;
int hebrewContinuosStart = 0;

void prepareCalendar() {
  // 1TISHRAY5700 = 14.9.1939
  // 1TISHRAY5600 = 9.9.1839 (doesn't work)
  // 1TISHRAY5650 = 26.9.1889 (doesn't work)
  // 1TISHRAY5690 = 5.10.1929
  // this just works in our current range from 1929 to 2039 (gets incorrect before)
  hebrewContinuosStart = continuosFromGregorian(5,10,1929); // first rosh hashanah in list
  hebrewStartYear = 5690;
  gregorianStartYear = 1930;
  yearCount = 200;
  printf("%d\n", continuosFromGregorian(9,7,2026) % 7);
}

unsigned int continuosFromHebrew(int day, int month, int year) {
  unsigned int ret = hebrewContinuosStart;
  int months[13] = {30,-1,-1,29,30,-1,-1,30,29,30,29,30,29};
  for (int y = hebrewStartYear; y < year; y++) {
    int daysInYear = daysForHebrewYear(y+1)-daysForHebrewYear(y);
    if (hebrewLeapYear(y)) {months[5] = 30; months[6] = 29;} else {months[5] = 29; months[6] = 0;}
    months[1] = (daysInYear % 10) == 5 ? 30 : 29;
    months[2] = (daysInYear % 10) == 3 ? 29 : 30;
    for (int j = 0; j < 13; j++) {ret += months[j];}
  }
  int daysInYear = daysForHebrewYear(year+1)-daysForHebrewYear(year);
  if (hebrewLeapYear(year)) {months[5] = 30; months[6] = 29;} else {months[5] = 29; months[6] = 0;}
  months[1] = (daysInYear % 10) == 5 ? 30 : 29;
  months[2] = (daysInYear % 10) == 3 ? 29 : 30;
  for (int j = 0; j < month-1; j++) {ret += months[j];}
  ret += day - 1;
  return ret;
}

void hebrewFromContinuos(unsigned int continuos, int &day, int &month, int &year) {
  year = hebrewStartYear;
  continuos -= hebrewContinuosStart;
  while(1==1) {
    int daysInYear = daysForHebrewYear(year+1)-daysForHebrewYear(year);
    if (continuos < daysInYear) break;
    continuos -= daysInYear;
    year++;
  }
  int months[13] = {30,-1,-1,29,30,-1,-1,30,29,30,29,30,29};
  int daysInYear = daysForHebrewYear(year+1)-daysForHebrewYear(year);
  if (hebrewLeapYear(year)) {months[5] = 30; months[6] = 29;} else {months[5] = 29; months[6] = 0;}
  months[1] = (daysInYear % 10) == 5 ? 30 : 29;
  months[2] = (daysInYear % 10) == 3 ? 29 : 30;
  month = 0;
  int a = continuos;
  for (int i = 0; i < a; i++) {
    if (continuos >= months[month % 13]) {
      continuos -= months[month % 13];
      month++;
    }
  }
  month = month % 13;
  month += 1;
  day = continuos + 1;
}

void getTimeFromContinuos(double continuos, int &hourN, int &minuteN, int &secondN) {
  double inDay = continuos - floor(continuos);
  int v = inDay * 24 * 60 * 60;
  secondN = v % 60; v /= 60;
  minuteN = v % 60; v /= 60;
  hourN = v % 24;
}

void printContinuos(unsigned int continuos) {
  int day, month, year;
  int day2, month2, year2;
  gregorianFromContinuos(continuos, day, month, year);
  hebrewFromContinuos(continuos, day2, month2, year2);
  printf("%d.%s.%d -> %d.%s.%d\n",day,monthsG[month-1],year,day2,monthsH[month2-1],year2);
}

int tupled(int k) {
  return (k & 15)+(k>>4)*10;
}

void buildParashatOrderForHebrewYear(int year) {
  bool leap0 = hebrewLeapYear(year-1);
  unsigned int continuos0 = continuosFromHebrew(1,1,year); unsigned int weekDay0 = continuos0 % 7;  bool sep0 = weekDay0 == 0 || weekDay0 == 1; // monday or tuesday of next year
  bool leap2 = hebrewLeapYear(year);
  unsigned int continuos2 = continuosFromHebrew(1,1,year+1); unsigned int weekDay2 = continuos2 % 7;  bool sep2 = weekDay2 == 0 || weekDay2 == 1; // monday or tuesday of next year

  // negatives reach into the last year
  // missing shabbats that fall on holidays where there can't be a parashat
  int p = -5;
  for (int i = 0; i < 70; i++) {
    int k = p;
    if (k > 53) k = 53;
    if (leap0) {
    } else {
      if (k == VAYEKHEL) {k = VAYEKHEL_PEKUDEI; p++;}
      if (k == TAZRIA) {k = TAZRIA_METZORA; p++;}
      if (k == ACHAREIMOT) {k = ACHAREIMOT_KEDOSHIM; p++;}
      if (k == BEHAR) {k = BEHAR_BECHUKOTEI; p++;}
      //if (k == CHUKAT) {k = CHUKAT_BALAK; p++;}
      if (k == MATOT) {k = MATOT_MASEI; p++;}
      if ((!sep0) && k == NITZAVIM) {k = NITZAVIM_VAYELECH; p++;}
    }
    if (k < 0) k = 0; if (k >= 54+9) k = 53+9;
    parashatPerShabbat[i] = k;
    p++;
  }
  parashatPerShabbat[69] = DIDNTCALC;
}

void showTranslationView() {
  ImGui::Begin("Converter",0,ImVec2(400,600));

  static unsigned int weekDay = 0;
  static int dayH=1, monthH = 1, yearH = 5783; static bool recalcH = false; static int parashatWeek = 5;
  static int dayG=9, monthG = 7, yearG = 2026; static bool recalcG = false;
  static int dayB=1, monthB=1, yearB=5783;
  static int dayB2=1, monthB2=1, yearB2=5783;
  static bool afterSunset = false; static int sunsetti = 0;
  static bool init = true;
  if (init) {
    init = false;
    int rtc_seconds = rtcRead(0);
    int rtc_minutes = rtcRead(2);
    int rtc_hours   = rtcRead(4);
    int rtc_day     = rtcRead(7);
    int rtc_month   = rtcRead(8);
    int rtc_year    = rtcRead(9);
    dayG = tupled(rtc_day);
    monthG = tupled(rtc_month);
    yearG = tupled(rtc_year)+2000;
    buildParashatOrderForHebrewYear(5783);
    recalcG = true;
  }

  ImGui::Text("Conversion may be inaccurate %s", currentTimeString().c_str());
  int add = 0;
  ImGui::Text("Day"); ImGui::SameLine(); if (ImGui::Button("-##D")) {recalcG = true; recalcH = true; add = -1;} ImGui::SameLine(); if (ImGui::Button("+##D")) {recalcG = true; recalcH = true; add = 1;}
  ImGui::SameLine();
  ImGui::Text("Week"); ImGui::SameLine(); if (ImGui::Button("-##W")) {recalcG = true; recalcH = true; add = -7;} ImGui::SameLine(); if (ImGui::Button("+##W")) {recalcG = true; recalcH = true; add = 7;}
  ImGui::Separator();
  ImGui::Text("%s %s", days[weekDay], weekDay == 5 ? "-> hebrew shabbat on this day" : "");
  ImGui::Separator();
  ImGui::Text("Hebrew year (from %d to %d)", hebrewStartYear, hebrewStartYear + yearCount);
  ImGui::PushItemWidth(7*2+20*2+4);
  if (ImGui::InputInt("##SHOWTRANSLATIONVIEWDAYH",&dayH,1,1)) {recalcH = true;} if (dayH < 1) dayH = 1; if (dayH > 30) dayH = 30;
  ImGui::PopItemWidth();
  ImGui::SameLine();
  ImGui::PushItemWidth(7*8+20*1+4);
  monthH--;ImGui::SameLine(); if (ImGui::Combo("##SHOWTRANSLATIONVIEWMONTHH",&monthH, monthsH, 13)) {recalcH = true;} monthH++; if (monthH < 1) monthH = 1; if (monthH > 13) monthH = 13;
  ImGui::PopItemWidth();
  ImGui::SameLine();
  ImGui::PushItemWidth(7*4+20*2+4);
  if (ImGui::InputInt("##SHOWTRANSLATIONVIEWYEARH",&yearH,1,1)) {recalcH = true;} if (yearH < hebrewStartYear+1) yearH = hebrewStartYear+1; if (yearH >= hebrewStartYear + yearCount) yearH = hebrewStartYear + yearCount-1;
  ImGui::PopItemWidth();
  int daysInYear = daysForHebrewYear(yearH+1)-daysForHebrewYear(yearH);
  const char *types[3] = {"Defective", "Regular", "Abundant"}; int type = 0;
  switch(daysInYear) {
  case 353: case 353+30: type = 0; break;
  case 354: case 354+30: type = 1; break;
  case 355: case 355+30: type = 2; break;
  }
  ImGui::Text("%s %s with %d days.",types[type],hebrewLeapYear(yearH) ? "leap year" : "year", daysInYear);
  ImGui::Text("%s", monthsHZ[monthH-1]);
  if ((yearH % 7)==0) ImGui::Text("Sabbatjahr (%dst)",yearH/7);
  if ((yearH % 49)==1) ImGui::Text("Erlassjahr (%dst) (not official)",yearH/49);

  if (ImGui::Checkbox("After sunset##SHOWTRANSLATIONVIEWAFTERSUNSETH", &afterSunset)) {sunsetti = afterSunset ? 1 : 0; recalcH = true;}

  ImGui::Separator();
  ImGui::Text("Gregorian year (from %d to %d)", gregorianStartYear, gregorianStartYear + yearCount);
  ImGui::PushItemWidth(7*2+20*2+4);
  if (ImGui::InputInt("##SHOWTRANSLATIONVIEWDAYG",&dayG,1,1)) {recalcG = true;} if (dayG < 1) dayG = 1; if (dayG > 31) dayG = 31;
  ImGui::PopItemWidth();
  ImGui::SameLine();
  ImGui::PushItemWidth(7*8+20*1+4);
  monthG--;ImGui::SameLine(); if (ImGui::Combo("##SHOWTRANSLATIONVIEWMONTHG",&monthG, monthsG, 12)) {recalcG = true;} monthG++; if (monthG < 1) monthG = 1; if (monthG > 12) monthG = 12;
  ImGui::PopItemWidth();
  ImGui::SameLine();
  ImGui::PushItemWidth(7*4+20*2+4);
  if (ImGui::InputInt("##SHOWTRANSLATIONVIEWYEARG",&yearG,1,1)) {recalcG = true;} if (yearG < gregorianStartYear + 1) yearG = gregorianStartYear + 1; if (yearG >= gregorianStartYear + yearCount) yearG = gregorianStartYear + yearCount-1;
  ImGui::PopItemWidth();
  daysInYear = (yearG & 3) == 0 ? 366 : 365;
  ImGui::Text("%s with %d days.",(yearG & 3) == 0 ? "Schaltjahr" : "Year", daysInYear);
  ImGui::Separator();
  ImGui::Text("Last beresheet reading %d.%s.%d, %d.%s.%d",dayB,monthsH[monthB-1],yearB,dayB2,monthsG[monthB2-1],yearB2);
  if (parashatWeek >= 5) {
    const char *parashat = parashats[parashatPerShabbat[parashatWeek]];
    const char *parashatContent = parashatContents[parashatPerShabbat[parashatWeek]];
    ImGui::Text("Parashat(currently incorrect): %s (week %d)", parashat,parashatWeek-5+1);
    ImGui::TextWrapped("%s", parashatContent);
  }

  ImGui::Separator();
  if (monthH == 1) { // TISHREY
    if (dayH == 1) {ImGui::Text("Rosh Hashanah (Kopf des Jahres) / Jahres Beginn");}
    if (dayH == 10) {ImGui::Text("Jom Kippur (Versoehnungstag)");}
    if (dayH >= 15 && dayH < 15+7) {ImGui::Text("Sukkot (Laubhuettenfest)");}
    if (dayH == 22) {ImGui::Text("Shmini Atzaret (Grosse Versammlung?)");}
    if (dayH == 23) {ImGui::Text("Simchat Torah (Tag der Torah Freude)");}
    if (dayH == dayB) {ImGui::Text("Shabbat Bereshit (Start of Torah with Bereshit)");}
  }
  int omer = -1;
  if (dayH == 1) {
    ImGui::Text("Begin des Monats, Rosh Chodesh");
  }
  int channukah = -1;
  if (monthH == 3) { // KISLEV
    if (dayH >= 25) channukah = dayH - 25 + 1;
  }
  if (monthH == 4) { // TEWET
    unsigned int continuos = continuosFromHebrew(25,3,yearH)+8;
    int dayB, monthB, yearB;
    hebrewFromContinuos(continuos, dayB, monthB, yearB);
    if (dayH < dayB) channukah = dayH + 8-dayB + 1;
  }
  if (monthH == 8) { // NISSAN
    if (dayH == 15) {ImGui::Text("Pessach, ?Seder? Lamm");}
    if (dayH == 16) {ImGui::Text("Pessach");}
    if (dayH >= 15) omer = dayH-15+1;
  }
  if (monthH == 5) { // SHVAT
    if (dayH == 15) {ImGui::Text("New year of the trees (Tu Bi Schwat)");}
  }
  if (monthH == 9) { // IJAR
    omer = dayH+30-15+1;
  }
  if (monthH == 10) { // SIVAN
    omer = dayH+30-15+29+1;
    if (omer > 49) omer = -1;
    if (dayH == 6) {ImGui::Text("Shavuot");}
  }
  if (monthH == 11) { // TAMMUZ
    if (dayH >= 17) {ImGui::Text("3 Wochen der Enge (three weeks of Narrowness)");}
  }
  if (monthH == 12) { // AV
    if (dayH <= 9) {ImGui::Text("3 Wochen der Enge (three weeks of Narrowness)");}
    if (dayH == 9) {ImGui::Text("Der neunte von Loewe. Tisha B Av.");}
  }
  if (monthH == 13) { // ELUL
    ImGui::Text("Shofar is blown");
  }
  if (channukah >= 1) {
    ImGui::Text("Channukah day %d (Abends Kerzen)", channukah);
  }
  if (omer >= 1) {
    int ow = (omer-1)/7+1;
    int od = ((omer-1) % 7)+1;
    ImGui::Text("(Nachts)Omer %d week %d day %d : %s in the vessel of %s", omer, ow, od, sephiras[3+od], sephiras[3+ow]);
  }

  bool dateUpdated = false;

  if (recalcG) {
    recalcG = false;
    unsigned int continuos = continuosFromGregorian(dayG,monthG,yearG) + add;
    hebrewFromContinuos(continuos - sunsetti, dayH, monthH, yearH);
    gregorianFromContinuos(continuos, dayG, monthG, yearG);
    dateUpdated = true;
  }

  if (recalcH) {
    recalcH = false;
    unsigned int continuos = continuosFromHebrew(dayH,monthH,yearH);
    gregorianFromContinuos(continuos + sunsetti, dayG, monthG, yearG);
    hebrewFromContinuos(continuos, dayH, monthH, yearH);
    dateUpdated = true;
  }

  if (dateUpdated) {
    unsigned int continuos = continuosFromGregorian(dayG,monthG,yearG) - sunsetti;
    weekDay = continuos % 7;

    unsigned int continuos2 = continuosFromHebrew(23,1,yearH); continuos2 = (continuos2+1)/7*7+5;
    hebrewFromContinuos(continuos2, dayB, monthB, yearB);
    gregorianFromContinuos(continuos2, dayB2, monthB2, yearB2);
    unsigned int continuos3 = continuosFromHebrew(dayH,monthH,yearH);
    parashatWeek = floor(((int)continuos3 - (int)continuos2 + 6)/7.0) + 5; if (parashatWeek < 0) parashatWeek = 0; if (parashatWeek >= 70) parashatWeek = 69;
    buildParashatOrderForHebrewYear(yearH);
  }
 
  ImGui::End();
}

int main(int argc, const char *argv[]) {

  prepareCalendar();
  
  if (!glVesa(1024,768,16)) {printf("Error: Could not initialize video mode.\n"); return 0;}

  InitImGui(glFrameBufferWidth,glFrameBufferHeight);

  bool quit = false;
  while(!quit) {

    if (currentKey == GL_VK_END) quit = true;

    glClearColor(0.6,0.8,1.0,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    ImGuiNewFrame();

    showTranslationView();

    ImGui::Render();
      
    glRefresh();
  }

  glDone();

  return 0;
}
