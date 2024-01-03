#include <goopylib/goopylib.h>
#include <iostream>

int getPackingAlgorithmChoice() {
    const char *choices = R""""(
    Choose an algorithm: {
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

    Enter Choice: )"""";

    std::string choice;
    std::cout << choices;
    getline(std::cin, choice);

    if (choice.empty()) {
        return -1;
    }
    return std::stoi(choice);
}

gp::packing::shelf::ShelfPackingAlgorithm *getPackingAlgorithm(int choice) {
    switch (choice) {
        case -1:
            return new gp::packing::shelf::BestAreaFit(800, 800);
        case 1:
            return new gp::packing::shelf::NextFit(800, 800);
        case 2:
            return new gp::packing::shelf::FirstFit(800, 800);
        case 3:
            return new gp::packing::shelf::BestWidthFit(800, 800);
        case 4:
            return new gp::packing::shelf::WorstWidthFit(800, 800);
        case 5:
            return new gp::packing::shelf::BestHeightFit(800, 800);
        case 6:
            return new gp::packing::shelf::WorstHeightFit(800, 800);
        case 7:
            return new gp::packing::shelf::BestAreaFit(800, 800);
        case 8:
            return new gp::packing::shelf::WorstAreaFit(800, 800);
        default:
            throw std::invalid_argument("Invalid algorithm choice");
    }
}

void createRandomItems(int n, std::vector<Ref<gp::packing::Item>>& items) {
    items.reserve(n);
    for (int i = 0; i < n; i++) {
        items.emplace_back(new gp::packing::Item(5 + (float) (rand() % 6500) / 100,
                                                 5 + (float) (rand() % 7500) / 100));
    }
}

void printPackingRatio(std::vector<Ref<gp::packing::ShelvedBin>> &bins) {
    float packingRatio = 0;

    for (int i = 0; i < bins.size(); i++) {
        packingRatio += bins[i]->packingRatio();
        std::cout << "Packing Ratio for Bin " << i << ": " << 100 * bins[i]->packingRatio() << "%\n";
    }

    std::cout << "Average Packing Ratio: " << 100 * packingRatio / (float) bins.size() << "%\n";
}

void showPage(int page, std::vector<std::vector<gp::Rectangle>> &objects) {
    for (int i = 0; i < objects.size(); i++) {
        for (auto &obj: objects[i]) {
            obj.hide(i != page);
        }
    }
}

void plotItemBins(std::vector<Ref<gp::packing::ShelvedBin>> &bins) {
    gp::Window window = {800, 800};
    window.getCamera().setProjection(0, window.getWidth(), 0, window.getHeight());

    std::vector<std::vector<gp::Rectangle>> objects;

    gp::Color colors[5] = {gp::Color(65, 110, 230),
                           gp::Color(190, 240, 140),
                           gp::Color(80, 60, 160),
                           gp::Color(220, 120, 140),
                           gp::Color(120, 220, 250)};

    for (auto bin: bins) {
        objects.emplace_back();

        for (int j = 0; j < bin->items().size(); j++) {
            auto item = bin->items()[j];
            auto obj = gp::Rectangle(item->p1(), item->p2());
            obj.setColor(colors[j % 5]);
            obj.draw(window);
            objects.back().push_back(obj);
        }
    }

    int page = 0;
    showPage(page, objects);

    while (window.isOpen()) {
        if (window.checkKey(GP_KEY_LEFT) or window.checkKey(GP_KEY_RIGHT)) {
            page += window.checkKey(GP_KEY_LEFT) ? -1 : 1;
            page %= bins.size();

            showPage(page, objects);

            while (window.checkKey(GP_KEY_LEFT) or window.checkKey(GP_KEY_RIGHT)) {
                gp::update();
            }
        }
        gp::update();
    }
}

int main() {
    gp::init();

    int choice = getPackingAlgorithmChoice();
    auto algorithm = getPackingAlgorithm(choice);

    std::vector<Ref<gp::packing::Item>> items;
    createRandomItems(500, items);

    algorithm->packAll(items);
    auto bins = algorithm->bins();
    delete algorithm;

    printPackingRatio(bins);
    plotItemBins(bins);

    gp::terminate();
    return 0;
}
