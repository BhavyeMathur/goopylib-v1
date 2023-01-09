#include <goopylib/goopylib.h>
#include <iostream>


int main() {
    gp::init();

    const char *choices = R""""(
    Choose an algorithm:
        ⏎ default

        Shelf Algorithms
        ----------------

        1. Shelf Next-Fit
        2. Shelf First-Fit

        3. Shelf Best Width Fit
        4. Shelf Worst Width Fit

        5. Shelf Best Height Fit
        6. Shelf Worst Height Fit

        7. Shelf Best Area Fit
        8. Shelf Worst Area Fit

        Oriented Shelf Algorithms
        -------------------------

        9. Oriented Shelf Next-Fit
        10. Oriented Shelf First-Fit

        11. Oriented Shelf Best Width Fit
        12. Oriented Shelf Worst Width Fit

        13. Oriented Shelf Best Height Fit
        14. Oriented Shelf Worst Height Fit

        15. Oriented Shelf Best Area Fit
        16. Oriented Shelf Worst Area Fit

    Enter Choice: )"""";

    std::string choice;
    std::cout << choices;
    getline(std::cin, choice);

    std::vector<gp::Ref<gp::packing::Item>> items;
    for (int i = 0; i < 500; i++) {
        items.push_back(gp::packing::Item::create(5 + (float) (rand() % 6500) / 100,
                                                  5 + (float) (rand() % 7500) / 100));
    }

    std::vector<gp::Ref<gp::packing::ShelvedBin>> bins;
    if (choice == "") {
        bins = gp::packing::shelf::packBestAreaFit(items, 800, 800);
    }
    else {
        switch (std::stoi(choice)) {
            case 1:
                bins = gp::packing::shelf::packNextFit(items, 800, 800);
                break;
            case 2:
                bins = gp::packing::shelf::packFirstFit(items, 800, 800);
                break;
            case 3:
                bins = gp::packing::shelf::packBestWidthFit(items, 800, 800);
                break;
            case 4:
                bins = gp::packing::shelf::packWorstWidthFit(items, 800, 800);
                break;
            case 5:
                bins = gp::packing::shelf::packBestHeightFit(items, 800, 800);
                break;
            case 6:
                bins = gp::packing::shelf::packWorstHeightFit(items, 800, 800);
                break;
            case 7:
                bins = gp::packing::shelf::packBestAreaFit(items, 800, 800);
                break;
            case 8:
                bins = gp::packing::shelf::packWorstAreaFit(items, 800, 800);
                break;
            case 9:
                bins = gp::packing::shelf::packOrientedNextFit(items, 800, 800);
                break;
            case 10:
                bins = gp::packing::shelf::packOrientedFirstFit(items, 800, 800);
                break;
            case 11:
                bins = gp::packing::shelf::packOrientedBestWidthFit(items, 800, 800);
                break;
            case 12:
                bins = gp::packing::shelf::packOrientedWorstWidthFit(items, 800, 800);
                break;
            case 13:
                bins = gp::packing::shelf::packOrientedBestHeightFit(items, 800, 800);
                break;
            case 14:
                bins = gp::packing::shelf::packOrientedWorstHeightFit(items, 800, 800);
                break;
            case 15:
                bins = gp::packing::shelf::packOrientedBestAreaFit(items, 800, 800);
                break;
            case 16:
                bins = gp::packing::shelf::packOrientedWorstAreaFit(items, 800, 800);
                break;
            default:
                throw std::invalid_argument("Invalid algorithm choice");
        }
    }

    auto window = gp::Window(800, 800);
    std::vector<std::vector<gp::Rectangle>> objects;

    gp::Color colors[5] = {gp::Color(65, 110, 230),
                           gp::Color(190, 240, 140),
                           gp::Color(80, 60, 160),
                           gp::Color(220, 120, 140),
                           gp::Color(120, 220, 250)};

    float packingRatio = 0;
    for (int i = 0; i < bins.size(); i++) {
        objects.emplace_back();
        auto bin = bins[i];

        for (int j = 0; j < bin->items().size(); j++) {
            auto item = bin->items()[j];

            auto obj = gp::Rectangle(item->p1(), item->p2());
            obj.setColor(colors[j % 5]);
            obj.move(window.getWidth() / -2, window.getHeight() / -2);

            if (i != 0) {
                obj.hide();
            }
            obj.draw(&window);
            objects.back().push_back(obj);
        }

        packingRatio += bin->packingRatio();
        std::cout << "Packing Ratio for Bin " << i << ": " << 100 * bin->packingRatio() << "%\n";
    }
    std::cout << "Average Packing Ratio: " << 100 * packingRatio / (float) bins.size() << "%\n";

    int page = 0;
    while (window.isOpen()) {
        if (window.checkKey(GP_KEY_LEFT) or window.checkKey(GP_KEY_RIGHT)) {
            page += window.checkKey(GP_KEY_LEFT) ? -1 : 1;
            page %= bins.size();

            for (int i = 0; i < objects.size(); i++) {
                for (auto &obj: objects[i]) {
                    obj.hide(i != page);
                }
            }

            while (window.checkKey(GP_KEY_LEFT) or window.checkKey(GP_KEY_RIGHT)) {
                gp::update();
            }
        }
        gp::update();
    }

    gp::terminate();
    return 0;
}
