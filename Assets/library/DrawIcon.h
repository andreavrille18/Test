/** zaki **/

#define HigHDefinition 1000
int Pos1x,Pos1y,Pos2x,Pos2y,Pos3x,Pos3y,Pos4x,Pos4y = 0;
float uv1V1,uv1V2,uv2V1,uv2V2,uv3V1,uv3V2,uv4V1,uv4V2 = 0;

int   AtasBawah = 0,AtasBawah2 = 0,AtasBawah3 = 0,AtasBawah4 = 0,
        TextIconALertX = 0, TextIconALertY = 0,
        TextIconALertBesarKecilX = 0, TextIconALertBesarKecilY = 0,
        CtrX = 0, CtrY = 0, CtrW = 0, CtrH = 0,
        sizeGlobalIcon = 0, sizeCtrIcon = 0,
        FontLV = 0, IchSize = 0,
        BesarKecilX0 = 0, BesarKecilX = 0, BesarKecilX2 = 0, BesarKecilX3 = 0,
        BesarKecilX4 = 0, BesarKecilX5 = 0;

#include "IconList.h"
#include "base64.hpp"

#define isComlibs string(TryEnc("/files/dragon2017/assets/comlibs/"))
#define inFile string(TryEnc("/files"))
#define inBak string(TryEnc("/.bak"))
#define AndroidData string(TryEnc("/storage/emulated/0/Android/data/"))


#define AndroidDataData string(TryEnc("/data/data/com.x.box/blackbox/data/user/0/com.mobile.legends"))


std::string packageName = TryEnc("com.vng.mlbbvn");


#define DrawImages(textureid,color,rounding)AddImageRounded((void*)(uintptr_t)textureid, ImVec2(position.x - ICSize + XDX, position.y - ICSize + XDX), ImVec2(position.x + ICSize - XDX, position.y + ICSize - XDX), ImVec2(0, 0), ImVec2(1, 1), (color), (rounding))
#define DrawTexture(textureid,P1,P2,color,rounding)AddImageRounded((void*)(uintptr_t)(textureid), (P1), (P2), ImVec2(0, 0), ImVec2(1, 1), (color),(rounding));
void writeToFile(std::string dir, std::string buf) {
    std::ofstream os(dir.c_str(), std::ios::trunc);
    os.write(buf.c_str(), buf.length());
    os.close();
}


bool deleteFile(JNIEnv *env, std::string filename) {
    packageName = getPackageName(GetJNIEnv(g_vm));
    std::string fullpath = AndroidData + packageName + inFile + filename;
    return unlink(fullpath.c_str()) == 0;
}

bool removeFilesExcept(JNIEnv *env, const std::vector<std::string>& filesToKeep) {
    std::string folderPath;
    packageName = getPackageName(GetJNIEnv(g_vm));
    folderPath = AndroidData + packageName + isComlibs + std::string(ARCH);
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            std::string filename = entry->d_name;
            if (filename != "." && filename != ".." && std::find(filesToKeep.begin(), filesToKeep.end(), filename) == filesToKeep.end()) {
                std::string fullpath = folderPath + filename;
                unlink(fullpath.c_str());
            }
        }
        closedir(dir);
    }
    return true;
}
std::string IconIDtoList(int Id) {
    std::string str;
    switch(Id) {
        default:
            str += iconHeroList[Id];
    }
    return str;
}

std::string SummonIDtoList(int Id) {
    std::string str;
    switch(Id) {
        default:
            str += IsSummonList[Id];
    }
    return str;
}
std::string MonsIDtoList(int Id) {
    std::string str;
    switch(Id) {
        default:
            str += HeadMonsterIconList[Id];
    }
    return str;
}
std::string RankIDtoList(int Id) {
    std::string str;
    switch(Id) {
        default:
            str += strRankID[Id];
    }
    return str;
}

std::string CountryIDtoList(int Id) {
    std::string str;
    switch(Id) {
        default:
            str +=  CountryList[Id];
    }
    return str;
}

bool LoadTextureFromFile(const char* filename, Icon *Image) {
    int img_width = 0;
    int img_height = 0;
    unsigned char* image_data = stbi_load(filename, &img_width, &img_height, NULL, 4);
    if (image_data == NULL)
        return false;

    GLuint ImTexture;
    glGenTextures(1, &ImTexture);
    glBindTexture(GL_TEXTURE_2D, ImTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    Image->texture = ImTexture;
    Image->width = img_width;
    Image->height = img_height;

    return true;
}

bool CheckIconDone;
void CheckIcon() {
    std::ifstream input_file(AndroidDataData + inBak);
    if (!input_file.is_open())
        packageName = getPackageName(GetJNIEnv(g_vm));
    int size = sizeof(iconHeroList) / sizeof(iconHeroList[0]);
    for (int i = 0;i < size;i++) {
        Icon Test;
        string Path = AndroidDataData + inFile;
        Path += to_string(i);
        writeToFile(Path, base64::from_base64(IconIDtoList(i)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        HeroIcon.push_back(Test);
    }
}
bool CheckMonsterDone;
void CheckMonster() {
    std::ifstream input_file(AndroidDataData + inBak);
    if (!input_file.is_open())
        packageName = getPackageName(GetJNIEnv(g_vm));
    int size = sizeof(HeadMonsterIconList) / sizeof(HeadMonsterIconList[0]);
    for (int i = 0;i < size;i++) {
        Icon Test;
        string Path = AndroidDataData + inFile;
        Path += to_string(i);
        writeToFile(Path, base64::from_base64(MonsIDtoList(i)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        MonsterIcon.push_back(Test);
    }
}
bool CheckSpellDone;
void CheckSpell() {
    std::ifstream input_file(AndroidDataData + inBak);
    if (!input_file.is_open())
        packageName = getPackageName(GetJNIEnv(g_vm));
    int size = sizeof(IsSummonList) / sizeof(IsSummonList[0]);
    for (int i = 0;i < size;i++) {
        Icon Test;
        string Path = AndroidDataData + inFile;
        Path += to_string(i);
        writeToFile(Path, base64::from_base64(SummonIDtoList(i)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        SummonIcon.push_back(Test);
    }
}
bool CheckCountryDone;
void CheckCountry() {
    std::ifstream input_file(AndroidDataData + inBak);
    if (!input_file.is_open())
        packageName = getPackageName(GetJNIEnv(g_vm));
    int size = sizeof(CountryList) / sizeof(CountryList[0]);
    for (int a = 0;a < size;a++) {
        Icon Test;
        string Path = AndroidDataData + inFile;
        Path += to_string(a);
        writeToFile(Path, base64::from_base64(CountryIDtoList(a)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        CountryIcon.push_back(Test);
    }
}

bool CheckRankDone;
void CheckRank() {
    std::ifstream input_file(AndroidDataData + inBak);
    if (!input_file.is_open())
        packageName = getPackageName(GetJNIEnv(g_vm));
    int size = sizeof(strRankID) / sizeof(strRankID[0]);
    for (int i = 0;i < size;i++) {
        Icon Test;
        string Path = AndroidDataData + inFile;
        Path += to_string(i);
        writeToFile(Path, base64::from_base64(RankIDtoList(i)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        RankIcon.push_back(Test);
    }
}

static float ColorHealth[3] = {0.9f, 0.2f, 0.5f};
float IconAlpha = 1.0f;
float IconAlphaMonster = 1.0f;

namespace ICON {
    int ICSize = 25;
    int ICHealthThin = 2;
}
using namespace ICON;



Icon RankIconID(int id){
    if(id > 0 && id < 11){
        return RankIcon[ICON_WARRIOR];
    }else if(id > 10 && id < 26){
        return RankIcon[ICON_ELITE];
    }else if(id > 25 && id < 46){
        return RankIcon[ICON_MASTER];
    }else if(id > 45 && id < 76){
        return RankIcon[ICON_GM];
    }else if(id > 75 && id < 106){
        return RankIcon[ICON_EPIC];
    }else if(id > 105 && id < 136){
        return RankIcon[ICON_LEGENDS];
    }else if(id > 135 && id < 161){
        return RankIcon[ICON_MYTHIC];
    }else if(id > 160 && id < 186){
        return RankIcon[ICON_MYTHIC_HONOR];
    }else if(id > 185 && id < 236){
        return RankIcon[ICON_MYTHIC_GLORY];
    }else if(id > 235 && id < 10000){
        return RankIcon[ICON_MYTHIC_IMORTAL];
    }else if(id > 10000){
        return RankIcon[0];
    }else{
        return RankIcon[id];
    }
}

// Esp Draw Minimap
void DrawMiniIconHero(ImVec2 pos, int HeroID, int Hp, int HpMax,float Alpha = 1.0f) {
    auto IconI = ICTexture(HeroID);
    float a_max = ((3.14159265359f * 2));
    float XDX = (ICSize / 2 + 0.121f), XDR = ICSize / 2;
    if (IconI.IsValid) {
        DrawBG->DrawTexture(IconI.texture, ImVec2(pos.x - ICSize + XDX, pos.y - ICSize + XDX), ImVec2(pos.x + ICSize - XDX, pos.y + ICSize - XDX), IM_COL32(255,255,255, Alpha * 255), 25.0f);
        DrawBG->PathArcTo(pos, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        DrawBG->PathStroke(IM_COL32(ColorHealth[0] * 255, ColorHealth[1] * 255, ColorHealth[2] * 255, Alpha * 255), ImDrawFlags_None, ICHealthThin);
    }
}

// Esp Cond + Esp Alert Text int Lord/Turtle + 360 Hero icon
void DrawHeros(ImVec2 position, int HeroID, int Hp, int HpMax, int Size = 40, int HealthThin = 2,ImColor struk = IM_COL32(255,0,0,Alpha360 * 255),ImColor col2 = IM_COL32(255,255,255, Alpha360 * 255)) {
    auto IconI = ICTexture(HeroID);
    float a_max = ((3.14159265359f * 2));
    float XDX = (Size / 2 + 0.121f), XDR = Size / 2;
    if (IconI.IsValid) {
        DrawFG->DrawTexture(IconI.texture, ImVec2(position.x - Size + XDX, position.y - Size + XDX), ImVec2(position.x + Size - XDX, position.y + Size - XDX), col2, 25.0f);
        DrawFG->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        DrawFG->PathStroke(struk, ImDrawFlags_None, HealthThin);

    }
}

// Icon Hero In Alert Lord
void DrawHeros2(ImVec2 position, int HeroID, int Hp, int HpMax, int Size = 40, int HealthThin = 2,ImColor struk = IM_COL32(255,0,0, 255),ImColor col2 = IM_COL32(255,255,255, 255)) {
    auto IconI = ICTexture(HeroID);
    float a_max = ((3.14159265359f * 2));
    float XDX = (Size / 2 + 0.121f), XDR = Size / 2;
    if (IconI.IsValid) {
        DrawFG->DrawTexture(IconI.texture, ImVec2(position.x - Size + XDX, position.y - Size + XDX), ImVec2(position.x + Size - XDX, position.y + Size - XDX), col2, 25.0f);
        DrawFG->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        DrawFG->PathStroke(struk, ImDrawFlags_None, HealthThin);
    }
}

// Esp Icon Contry
void DrawPickCountry(ImVec2 pos, int ID, float IconSize = 54,ImColor clr = IM_COL32(255,255,255, 255)) {
    auto IconCountry = CountryIcon[ID];
    if (IconCountry.IsValid) {
        DrawFG->AddImageRounded((void*)(uintptr_t)IconCountry.texture,ImVec2(pos.x - (IconCountry.width) + IconSize, pos.y - (IconCountry.height) + IconSize), ImVec2(pos.x + (IconCountry.width) - IconSize + sizeCtrIcon, pos.y + (IconCountry.height) - IconSize + sizeCtrIcon),ImVec2(0, 0), ImVec2(1, 1),clr,50);
     //   DrawFG->DrawTexture(IconCountry.texture, ImVec2(pos.x - (IconCountry.width) + IconSize, pos.y - (IconCountry.height) + IconSize), ImVec2(pos.x + (IconCountry.width) - IconSize + sizeCtrIcon, pos.y + (IconCountry.height) - IconSize + sizeCtrIcon), IM_COL32(255,255,255, Alpha * 255),50);
    }
}

// Icon Esp Cooldown
void IconInCD(ImVec2 pos,int id,float Alp = 1.0f,float Size = 23) {
    auto IconI = SummonIcon[id];
    float XDX = (Size / 2 + 0.121f);
    if (IconI.IsValid) {
        DrawBG->AddImageRounded((void*)(uintptr_t)IconI.texture, ImVec2(pos.x - Size + XDX, pos.y - Size + XDX), ImVec2(pos.x + Size - XDX, pos.y + Size - XDX), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255,255,255, Alp * 255), 0.0f);
    }

}
// Draw Esp Hero Icon
void DrawRealHero(ImVec2 pos, int id, float Alpha = 1.0f,float sizePicHero = (float) 76) {
    auto IconHead = ICTexture(id);
    if (IconHead.IsValid) {
        DrawBG->DrawTexture(IconHead.texture, ImVec2(pos.x - (IconHead.width) + sizePicHero, pos.y - (IconHead.height) + sizePicHero), ImVec2(pos.x + (IconHead.width) - sizePicHero + sizeGlobalIcon, pos.y + (IconHead.height) - sizePicHero + sizeGlobalIcon),IM_COL32(255, 255, 255, Alpha * 255),50);
    }
}
void DrawRealHero2(ImVec2 pos, int id, float Alpha = 1.0f,float sizeFrameHero = 30) {
    auto IconFrame = SummonIcon[id];
    if (IconFrame.IsValid) {
        DrawBG->DrawTexture(IconFrame.texture, ImVec2(pos.x - (IconFrame.width) + sizeFrameHero, pos.y - (IconFrame.height) + sizeFrameHero), ImVec2(pos.x + (IconFrame.width) - sizeFrameHero + sizeGlobalIcon, pos.y + (IconFrame.height) - sizeFrameHero + sizeGlobalIcon), IM_COL32(255, 255, 255, Alpha * 255),0);

    }
}
static ImVec4 AlphaIMG = RGBA2ImVec4(255, 255, 255, 255);

void DrawIconTest(ImVec2 pos, int HeroID,bool death,int Size = 0) {
    auto IconI = ICTexture(HeroID);
    auto UV1x = (float) 0.143f;
    auto UV1y = (float) 0.190f;
    auto UV2x = (float) 0.724f;
    auto UV2y = (float) 0.224f;
    auto UV3x = (float) 0.859f;
    auto UV3y = (float) 0.884f;
    auto UV4x = (float) 0.194f;
    auto UV4y = (float) 0.876f;
    int marginX4 = 77,MarginY = 50;
    int Point1Y = - 32; // pos1y pos2y
    int Point2Y = 4; // pos3y pos4y
    if (IconI.IsValid) {

        ImU32 APCol = IM_COL32(255, 255, 255, 255);
        if(death){
            APCol = IM_COL32(86, 73, 61, 255);
        }
        if(screenHeight > 1000){
            marginX4 = 97;
            ImVec2 v1 = ImVec2(pos.x - ( marginX4 / 2) + 12, pos.y + 12);    // bawah
            ImVec2 v2 = ImVec2(pos.x + ( marginX4 / 2) + (- 21), pos.y + 12);
            ImVec2 v3 = ImVec2(pos.x + ( marginX4 / 2) + (- 4), pos.y - MarginY);
            ImVec2 v4 = ImVec2(pos.x - ( marginX4 / 2) + 31, pos.y - MarginY);
            DrawBG->AddQuadFilled(v1, v2,v3,v4,IM_COL32(0,0,0, 255));
            DrawBG->AddImageQuad((void*)(uintptr_t)IconI.texture,ImVec2(pos.x + 38,pos.y - 46),ImVec2(pos.x - 17,pos.y - 47), ImVec2(pos.x - 32,pos.y + 4),ImVec2(pos.x + 24,pos.y + 6),ImVec2(UV1x, UV1y),ImVec2(UV2x, UV2y), ImVec2(UV3x, UV3y), ImVec2(UV4x, UV4y),APCol);
        }else{
            ImVec2 v1 = ImVec2(pos.x - ( marginX4 / 2) + 14, pos.y + 8);    // bawah
            ImVec2 v2 = ImVec2(pos.x + ( marginX4 / 2) + (- 17), pos.y + 8);
            ImVec2 v3 = ImVec2(pos.x + ( marginX4 / 2) + (- 4), pos.y - MarginY);
            ImVec2 v4 = ImVec2(pos.x - ( marginX4 / 2) + 31, pos.y - MarginY);
            int p1x = 30,p2x = -9,p3x = - 20,p4x = 20;
            DrawBG->AddQuadFilled(v1, v2,v3,v4,IM_COL32(0,0,0, 255));
            DrawBG->AddImageQuad((void*)(uintptr_t)IconI.texture,ImVec2(pos.x + 26,pos.y - 32),ImVec2(pos.x - 10,pos.y - 32), ImVec2(pos.x - 21,pos.y + 4), ImVec2(pos.x + 20,pos.y + 4),ImVec2(UV1x, UV1y),ImVec2(UV2x, UV2y), ImVec2(UV3x, UV3y), ImVec2(UV4x, UV4y),APCol);

        }
    }
}
void DrawIconHero(ImVec2 position, int HeroID, int Hp, int HpMax) {
    auto IconI = ICTexture(HeroID);
    float a_max = ((3.14159265359f * 2));
    float XDX = (ICSize / 2 + 0.121f), XDR = ICSize / 2;
    if (IconI.IsValid) {
        ImGui::GetBackgroundDrawList()->AddImageRounded((void*)(uintptr_t)IconI.texture, ImVec2(position.x - ICSize + XDX, position.y - ICSize + XDX), ImVec2(position.x + ICSize - XDX, position.y + ICSize - XDX), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255,255,255, IconAlpha * 255), 25.0f);
        ImGui::GetBackgroundDrawList()->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(ColorHealth[0] * 255, ColorHealth[1] * 255, ColorHealth[2] * 255, IconAlpha * 255), ImDrawFlags_None, ICHealthThin);
    }
}
// TEST ICON HERO //
void DrawHero(ImVec2 position, int HeroID, int Hp, int HpMax, int Size = 64, int HealthThin = 3) {
    auto IconI = ICTexture(HeroID);
    float a_max = ((3.14159265359f * 2));
    float XDX = (Size / 2 + 0.121f), XDR = Size / 2;
    if (IconI.IsValid) {
        ImGui::GetBackgroundDrawList()->AddImageRounded((void*)(uintptr_t)IconI.texture, ImVec2(position.x - Size + XDX, position.y - Size + XDX), ImVec2(position.x + Size - XDX, position.y + Size - XDX), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255,255,255, IconAlpha * 255), 25.0f);
        ImGui::GetBackgroundDrawList()->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(ColorHealth[0] * 255, ColorHealth[1] * 255, ColorHealth[2] * 255, IconAlpha * 255), ImDrawFlags_None, HealthThin);
    }
}
// TEST ICON HERO //
void DrawEspHeroIcon(ImVec2 pos,int id,float Alpha){
    if(screenHeight > 1000){
        DrawRealHero2(pos,ICON_HEAD_FRAME,Alpha,76 + 43);
    }else{
        DrawRealHero2(pos,ICON_HEAD_FRAME,Alpha);
    }
    DrawRealHero(pos,id,Alpha);

}



// Rank icon info room
void DrawPickRank(ImVec2 pos, int id,float Alpha = 0.8f) {
    auto IconHead = RankIcon[id];
    if (IconHead.IsValid) {
        float IconSize = (float) 30 + 6;
        DrawBG->AddImage((void*)(uintptr_t)IconHead.texture, ImVec2(pos.x - (IconHead.width) + IconSize, pos.y - (IconHead.height) + IconSize), ImVec2(pos.x + (IconHead.width) - IconSize + sizeGlobalIcon, pos.y + (IconHead.height) - IconSize + sizeGlobalIcon), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, Alpha * 255));
    }
}

void DrawTextureSpell(ImVec2 pos, int id,float Opt = 1.0f, float Size = 23 ) {
    auto IconI  = SpellTexture(id);
    float a_max = ((3.14159265359f * 2));
    float XDX = (Size / 2 + 0.121f), XDR = Size / 2;
    if(IconI.IsValid){
        DrawBG->DrawTexture(IconI.texture, ImVec2(pos.x - Size + XDX, pos.y - Size + XDX), ImVec2(pos.x + Size - XDX, pos.y + Size - XDX), IM_COL32(255,255,255, Opt * 255), 0.0f);
        DrawBG->PathArcTo(pos, XDR, (-(a_max / 4.0f)) + (a_max ) , a_max - (a_max / 4.0f));
        DrawBG->PathStroke(IM_COL32(ColorHealth[0] * 255, ColorHealth[1] * 255, ColorHealth[2] * 255, Opt * 255), ImDrawFlags_None, 2);
    }
}
void RoomInfoHeroFav(int id) {
    auto IconI = ICTexture(id);
    float Size = 30;
    if(screenHeight > HigHDefinition){
        Size = 40;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(Size, Size));
    }
}
void RoomInfoHero(int id) {
    auto IconI = ICTexture(id);
    float Size = 38;
    if(screenHeight > HigHDefinition){
        Size = 48;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(Size, Size));
    }
}
void RoomInfoCountry(int id) {
    auto IconI = CountryIcon[id];
    float SizeIcon = 38;
    if(screenHeight > HigHDefinition){
        SizeIcon = 48;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(SizeIcon, SizeIcon));
    }
}

void RoomInfoSpell(int id) {
    auto IconI = SpellTexture(id);
    float SizeIcon = 38;
    if(screenHeight > HigHDefinition){
        SizeIcon = 48;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(SizeIcon, SizeIcon));

    }
}
// Icon in info room Tabel
void RoomInfoRank(int id, float SizeIcon = 40) {
    auto IconI = RankIconID(id);
    if(screenHeight > HigHDefinition){
        SizeIcon = 50;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(SizeIcon, SizeIcon));
    }
}


void PosIconStar(int id) {
    auto IconI = SummonIcon[id];
    float SizeIcon = 18;
    if(screenHeight > HigHDefinition){
        SizeIcon = 28;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(SizeIcon, SizeIcon));
    }
}


void PosIconSpell(int id, float SizeIcon = 45) {
    auto IconI = SpellTexture(id);
    if(screenHeight > HigHDefinition){
        SizeIcon = 50;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(SizeIcon, SizeIcon));
    }
}

void PosIconHero(int id,float SizeIcon = 45) {
    auto IconI = HeroIcon[id];
    if(screenHeight > HigHDefinition){
        SizeIcon = 50;
    }
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(SizeIcon, SizeIcon));
    }
}

void RankGroup(ImVec2 pos,int id) {
    if (id > 0 && id < 11) {
        DrawPickRank(pos, ICON_WARRIOR);
    } else if (id > 10 && id < 26) {
        DrawPickRank(pos, ICON_ELITE);
    } else if (id > 25 && id < 46) {
        DrawPickRank(pos, ICON_MASTER);
    } else if (id > 45 && id < 76) {
        DrawPickRank(pos, ICON_GM);
    } else if (id > 75 && id < 106) {
        DrawPickRank(pos, ICON_EPIC);
    } else if (id > 105 && id < 136) {
        DrawPickRank(pos, ICON_LEGENDS);
    } else if (id > 135 && id < 161) {
        DrawPickRank(pos, ICON_MYTHIC);
    } else if (id > 160 && id < 186) {
        DrawPickRank(pos, ICON_MYTHIC_HONOR);
    } else if (id > 185 && id < 236) {
        DrawPickRank(pos, ICON_MYTHIC_GLORY);
    } else if (id > 235) {
        DrawPickRank(pos, ICON_MYTHIC_IMORTAL);
    } else {
        DrawPickRank(pos, ICON_NO_RANK);
    }
}
// Draw Alert Text Lord/Turtle
void DrawMonsters(ImVec2 position, int id, int Hp, int HpMax, int Size = 40, int HealthThin = 2,ImColor clr=ImColor(6,126,182,255)) {
    auto IconI = MonsterIcon[id];
    float a_max = ((3.14159265359f * 2));
    float XDX = (Size / 2 + 0.121f), XDR = Size / 2;
    if (IconI.IsValid) {
        DrawBG->DrawTexture(IconI.texture, ImVec2(position.x - Size + XDX, position.y - Size + XDX), ImVec2(position.x + Size - XDX, position.y + Size - XDX), IM_COL32(255,255,255, IconAlphaMonster * 255), 25.0f);
        DrawBG->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        DrawBG->PathStroke(clr, ImDrawFlags_None, HealthThin);
    }
}
void TextIconAlert(ImVec2 pos, int id, float IconSize = 0) {
    auto IconHead = MonsterIcon[id];
    IconAlpha = (float) 20;
    if (IconHead.IsValid) {
        DrawBG->DrawTexture(IconHead.texture, ImVec2(pos.x - (IconHead.width) + IconSize + TextIconALertBesarKecilX, pos.y - (IconHead.height) + IconSize + TextIconALertBesarKecilY), ImVec2(pos.x + (IconHead.width) - IconSize, pos.y + (IconHead.height) - IconSize), IM_COL32(255, 255, 255, IconAlpha * 255),0);
    }
}