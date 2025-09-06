#include <iostream>
#include <sstream>
#include <assert.h>
#include <algorithm>

namespace TelCoColorCoder
{
    enum MajorColor {WHITE, RED, BLACK, YELLOW, VIOLET};
    enum MinorColor {BLUE, ORANGE, GREEN, BROWN, SLATE};

    const char* MajorColorNames[] = {
        "White", "Red", "Black", "Yellow", "Violet"
    };
    const int numberOfMajorColors =
        sizeof(MajorColorNames) / sizeof(MajorColorNames[0]);

    const char* MinorColorNames[] = {
        "Blue", "Orange", "Green", "Brown", "Slate"
    };
    const int numberOfMinorColors =
        sizeof(MinorColorNames) / sizeof(MinorColorNames[0]);

    class ColorPair {
    private:
        MajorColor majorColor;
        MinorColor minorColor;

    public:
        ColorPair(MajorColor major, MinorColor minor):
            majorColor(major), minorColor(minor) {}

        MajorColor getMajor() const {
            return majorColor;
        }
        MinorColor getMinor() const {
            return minorColor;
        }
        std::string toString() const {
            std::string colorPairStr = MajorColorNames[majorColor];
            colorPairStr += " ";
            colorPairStr += MinorColorNames[minorColor];
            return colorPairStr;
        }
    };

    ColorPair getColorFromPairNumber(int pairNumber) {
        int zeroBasedPairNumber = pairNumber - 1;
        MajorColor majorColor =
            static_cast<MajorColor>(zeroBasedPairNumber / numberOfMinorColors);
        MinorColor minorColor =
            static_cast<MinorColor>(zeroBasedPairNumber % numberOfMinorColors);
        return ColorPair(majorColor, minorColor);
    }

    int getPairNumberFromColor(MajorColor major, MinorColor minor) {
        return major * numberOfMinorColors + minor + 1;
    }

    std::string getColorReferenceManual() {
        std::ostringstream oss;
        oss << "Color Code Reference Manual\n";
        oss << "----------------------------\n";
        for (int pairNumber = 1;
             pairNumber <= numberOfMajorColors * numberOfMinorColors;
             ++pairNumber)
        {
            ColorPair colorPair = getColorFromPairNumber(pairNumber);
            oss << pairNumber << " : " << colorPair.toString() << "\n";
        }
        return oss.str();
    }

    void printColorReferenceManual() {
        std::cout << getColorReferenceManual();
    }
}

// ---------------- Tests ----------------

void testNumberToPair(int pairNumber,
    TelCoColorCoder::MajorColor expectedMajor,
    TelCoColorCoder::MinorColor expectedMinor)
{
    TelCoColorCoder::ColorPair colorPair =
        TelCoColorCoder::getColorFromPairNumber(pairNumber);
    std::cout << "Got pair " << colorPair.toString() << std::endl;
    assert(colorPair.getMajor() == expectedMajor);
    assert(colorPair.getMinor() == expectedMinor);
}

void testPairToNumber(
    TelCoColorCoder::MajorColor major,
    TelCoColorCoder::MinorColor minor,
    int expectedPairNumber)
{
    int pairNumber = TelCoColorCoder::getPairNumberFromColor(major, minor);
    std::cout << "Got pair number " << pairNumber << std::endl;
    assert(pairNumber == expectedPairNumber);
}

void testColorReferenceManual()
{
    using namespace TelCoColorCoder;
    std::string manual = getColorReferenceManual();

    // Strong assert: check line count equals total pairs
    int expectedCount = numberOfMajorColors * numberOfMinorColors;
    int lineCount = std::count(manual.begin(), manual.end(), '\n') - 2; // exclude header
    assert(lineCount == expectedCount);

    // Strong assert: first and last mappings correct
    assert(manual.find("1 : White Blue") != std::string::npos);
    assert(manual.find("25 : Violet Slate") != std::string::npos);

    // Ensure all entries are unique
    for (int i = 1; i <= expectedCount; i++) {
        ColorPair cp = getColorFromPairNumber(i);
        std::string entry = std::to_string(i) + " : " + cp.toString();
        assert(manual.find(entry) != std::string::npos);
    }
}

// ---------------- Main ----------------

int main() {
    testNumberToPair(4, TelCoColorCoder::WHITE, TelCoColorCoder::BROWN);
    testNumberToPair(5, TelCoColorCoder::WHITE, TelCoColorCoder::SLATE);

    testPairToNumber(TelCoColorCoder::BLACK, TelCoColorCoder::ORANGE, 12);
    testPairToNumber(TelCoColorCoder::VIOLET, TelCoColorCoder::SLATE, 25);

    testColorReferenceManual();

    // Print manual for wiring personnel
    TelCoColorCoder::printColorReferenceManual();

    return 0;
}