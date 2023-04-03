#include <goopylib/goopylib.h>
#include <iostream>


void MillionTriangles() {
    auto window = gp::Window(900, 900);

    int N = 4096;
    float ds = 900.0f / (float) N;

    std::vector<gp::Triangle> triangles;

    for (int i = 0; i < N; i++) {
        float x = i * ds - 450.0f;

        for (int j = 0; j < N; j++) {
            float y = j * ds - 450.0f;
            triangles.push_back({{x, y}, {x + ds, y}, {x + ds / 2, y + ds}});
        }
    }

    for (auto obj: triangles) {
        obj.draw(&window);
    }

    gp::setBufferSwapInterval(0);
    uint32_t frames = 0;
    auto start = gp::getTime();

    while (window.isOpen()) {
        gp::update();
        frames++;
    }

    auto dt = gp::getTime() - start;
    std::cout << dt / (float) frames << "\n";
    std::cout << (float) frames / dt << "\n";
}


int main() {
    gp::init();

    auto window = gp::Window(900, 900);
    auto controller = gp::CameraController(&window);
    controller.setZoomKeys(GP_KEY_UP, GP_KEY_DOWN);

    auto EdwardianScript = gp::Font::load("/Applications/Microsoft Word.app/Contents/Resources/DFonts/EdwardianScriptITC.ttf");
    auto FranklinGothic = gp::Font::load("/Applications/Microsoft Word.app/Contents/Resources/DFonts/Franklin Gothic Heavy.ttf");
    auto Calbriz = gp::Font::load("/Applications/Microsoft Word.app/Contents/Resources/DFonts/Calibriz.ttf");
    auto Bauhaus = gp::Font::load("/Applications/Microsoft Word.app/Contents/Resources/DFonts/Bauhaus93.ttf");
    auto SegoeBold = gp::Font::load("/Applications/Microsoft Word.app/Contents/Resources/DFonts/Segoe Print Bold.ttf");
    auto Arial = gp::Font::load("/Applications/Microsoft Word.app/Contents/Resources/DFonts/Arial.ttf");

    gp::Text("Basic", {-430, 20}, 75).draw(&window);
    gp::Text("tiny", {-430, -200}, 15).draw(&window);
    gp::Text("Fancyyy", {-200, 20}, 75, EdwardianScript).draw(&window);
    gp::Text("Franklin.", {50, 20}, 75, FranklinGothic).draw(&window);

    gp::Text::setDefaultDirection(gp::TextDirection::RTL);
    gp::Text("מישהו יודע איך קוראים עברית", {-430, -100}, 25).draw(&window);

    auto Arabic = gp::Font::load("/Library/Fonts/KFGQPC Uthmanic Script HAFS Regular.otf");
    gp::Text::setDefaultScript(HB_SCRIPT_ARABIC);
    gp::Text::setDefaultLanguage("ar");

    gp::Text("تعليق على \"حكاية الأشياء\" من ناشونال جيوغرافك", {-430, 220}, 19).draw(&window);
    gp::Text("انفعلت مع هذا الفيديو على مستويين، أولهما تركيز المذيعة على الدور الذي يلعبه الإنسان في نظام الاقتصاد الاستهلاكي والذي عادة لا يُذكر في التفسيرات", {-430, 200}, 19).draw(&window);
    gp::Text("الاقتصادية أو علم الاقتصاد بشكل عام. فتخبرنا المذيعة بأن علماء الاقتصاد قد رسموا صورة منظمة وبسيطة ليفسروا هذا النظام الاقتصادي الاستهلاكي بشكل", {-430, 180}, 19).draw(&window);
    gp::Text("امبسط وكأنه نظام متكافئ بدون سلبيات أو مشاكل. ولكن بالطبع هذا النظام له تأثير لا يستهان به على حياة الانسان. وثانيهما، المذيعة تحاول أن تغير المفهوم الشائع", {-430, 160}, 19).draw(&window);
    gp::Text("لهذا النظام، فتركيزها الأول ليس على رحلة \"الأشياء\" والإنسان الذي لولاه لما كان النظام موجود قط. الإنسان، حسب هذه المذيعة، يلعب الدور الأساسي في هذا", {-430, 140}, 19).draw(&window);
    gp::Text("النظام، فهو موجود في كل مرحلة من النظام، من الاستخراج إلى الرمي.", {-430, 120}, 19).draw(&window);

    auto Hindi = gp::Font::load("/Library/Fonts/Mangal.ttf");
    gp::Text::setDefaultDirection(gp::TextDirection::LTR);
    gp::Text::setDefaultScript(HB_SCRIPT_DEVANAGARI);
    gp::Text::setDefaultLanguage("hi");

    gp::Text("जब बैग एंड के श्री बिल्बो बैगिन्स ने घोषणा की कि वह जल्द ही अपना सौ ग्यारहवां जन्मदिन मनाएंगे", {-430, -50}, 20).draw(&window);

    while (window.isOpen()) {
        gp::update();
        controller.update();
    }

    gp::terminate();
    return 0;
}
