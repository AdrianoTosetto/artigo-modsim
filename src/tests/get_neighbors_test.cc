bool topRight() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(0, 4).setIsAlive(true);
    hp.getCellRef(1, 3).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::TOP_RIGHT, 2);
}

bool topLeft() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(0, 0).setIsAlive(true);
    hp.getCellRef(1, 1).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::TOP_LEFT, 2);
}

bool top() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(0, 2).setIsAlive(true);
    hp.getCellRef(1, 2).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::TOP, 2);
}

bool right() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(2, 4).setIsAlive(true);
    hp.getCellRef(2, 3).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::RIGHT, 2);
    hp.display();
}

bool left() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(2, 0).setIsAlive(true);
    hp.getCellRef(2, 1).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::LEFT, 2);
    hp.display();
}

bool bottomRight() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(4, 4).setIsAlive(true);
    hp.getCellRef(3, 3).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::BOTTOM_RIGHT, 2);
    hp.display();
}

bool bottomLeft() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(4, 0).setIsAlive(true);
    hp.getCellRef(3, 1).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::BOTTOM_LEFT, 2);
    hp.display();
}

bool bottom() {
    HostPathogen<HostPathogenCell> hp(15, 15);
    hp.getCellRef(4, 2).setIsAlive(true);
    hp.getCellRef(3, 2).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::BOTTOM, 2);
    hp.display();
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
