#include "matrix.h"

bool DownExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    for (uint64_t x = 0; x < max_x; x++) {
        if (mass[max_y - 1][x] >= 4) {
            return true;
        }
    }
    return false;
}

bool LeftExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    for (uint64_t y = 0; y < max_y; y++) {
        if (mass[y][0] >= 4) {
            return true;
        }
    }
    return false;
}

bool RightExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    for (uint64_t y = 0; y < max_y; y++) {
        if (mass[y][max_x - 1] >= 4) {
            return true;
        }
    }
    return false;
}

bool UpExpansion(Vector<Vector<uint64_t>>& mass, uint64_t& max_x) {
    for (uint64_t x = 0; x < max_x; x++) {
        if (mass[0][x] >= 4) {
            return true;
        }
    }
    return false;
}

bool MoreThanFour(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    for (uint64_t y = 0; y < max_y; ++y) {
        for (uint64_t x = 0; x < max_x; ++x) {
            if (mass[y][x] >= 4) {
                return true;
            }
        }
    }
    return false;
}

bool EqualFour(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    for (uint64_t y = 0; y < max_y; ++y) {
        for (uint64_t x = 0; x < max_x; ++x) {
            if (mass[y][x] == 4) {
                return true;
            }
        }
    }
    return false;
}

void MakePicture(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    while (MoreThanFour(mass, max_x, max_y)) {
        bool need_right = RightExpansion(mass, max_x, max_y);
        bool need_down = DownExpansion(mass, max_x, max_y);
        bool need_left = LeftExpansion(mass, max_x, max_y);
        bool need_up = UpExpansion(mass, max_x);

        if (need_up) {
            mass.insert(mass.begin(), Vector<uint64_t>(max_x, 0));
            max_y += 1;
        }
        if (need_down) {
            mass.push_back(Vector<uint64_t>(max_x, 0));
            max_y += 1;
        }

        if (need_left && need_right) {
            for (auto& row : mass) {
                row.push_back(0);
                row.insert(row.begin(), 0);
            }
            max_x += 2;
        } 
        else if (need_right) {
            for (auto& row : mass) {
                row.push_back(0);
            }
            max_x += 1;
        }
        else if (need_left) {
            for (auto& row : mass) {
                row.insert(row.begin(), 0);
            }
            max_x += 1;
        }

        Scatter(mass, max_x, max_y);
    }
}

void Scatter(Vector<Vector<uint64_t>>& mass, uint64_t max_x, uint64_t max_y) {
    Vector<Vector<uint64_t>> copymass = mass;
    for (uint64_t y = 0; y < max_y - 1; ++y) {
        for (uint64_t x = 0; x < max_x - 1; ++x) {
            if (mass[y][x] >= 4) {
                copymass[y][x] -= 4;

                if (y + 1 < max_y) copymass[y + 1][x]++;
                if (y > 0) copymass[y - 1][x]++;
                if (x + 1 < max_x) copymass[y][x + 1]++;
                if (x > 0) copymass[y][x - 1]++;
            }
        }
    }
    mass = std::move(copymass);
}

void IterationOfPicture(Vector<Vector<uint64_t>>& mass, uint64_t& max_x, uint64_t& max_y) {
    bool need_right = RightExpansion(mass, max_x, max_y);
    bool need_down = DownExpansion(mass, max_x, max_y);
    bool need_left = LeftExpansion(mass, max_x, max_y);
    bool need_up = UpExpansion(mass, max_x);

    if (need_up) {
        mass.insert(mass.begin(), Vector<uint64_t>(max_x, 0));
        max_y += 1;
    }
    if (need_down) {
        mass.push_back(Vector<uint64_t>(max_x, 0));
        max_y += 1;
    }

    if (need_left && need_right) {
        for (auto& row : mass) {
            row.push_back(0);
            row.insert(row.begin(), 0);
        }
        max_x += 2;
    } 
    else if (need_right) {
        for (auto& row : mass) {
            row.push_back(0);
        }
        max_x += 1;
    }
    else if (need_left) {
        for (auto& row : mass) {
            row.insert(row.begin(), 0);
        }
        max_x += 1;
    }

    Scatter(mass, max_x, max_y);
}
