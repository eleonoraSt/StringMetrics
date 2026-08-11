#include <QTest>

#include "..\include\editDistance.h"

class TestHamming: public QObject {
    Q_OBJECT
private slots:
    void identical() {
        std::string str1 = "aaa", str2 = "aaa";
        QCOMPARE(Hamming(str1, str2), 0);
        std::wstring str3 = L"Հայոց", str4 = L"Հայոց";
        QCOMPARE(Hamming(str3, str4), 0);
        std::u16string str5 = u"汉字", str6 = u"汉字";
        QCOMPARE(Hamming(str5, str6), 0);
    }

    void uneven() {
        bool error;
        std::string str1 = "a", str2 = "ab";
        try {
            Hamming(str1, str2);
            error = false;
        } catch (std::invalid_argument exc) {error = true;}
        QCOMPARE(error, true);
        std::string str3 = "ab", str4 = "a";
        try {
            Hamming(str3, str4);
            error = false;
        } catch (std::invalid_argument exc) {error = true;}
        QCOMPARE(error, true);
    }

    void substitution() {
        std::string str1 = "aaa", str2 = "cba";
        QCOMPARE(Hamming(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հայո!";
        QCOMPARE(Hamming(str3, str4), 1);
        std::u16string str5 = u"汉字", str6 = u"水字";
        QCOMPARE(Hamming(str5, str6), 1);
    }

    void transposition() {
        std::string str1 = "abc", str2 = "acb";
        QCOMPARE(Hamming(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հյաոց";
        QCOMPARE(Hamming(str3, str4), 2);
        std::u16string str5 = u"汉字", str6 = u"字汉";
        QCOMPARE(Hamming(str5, str6), 2);
    }

    void mixed() {
        std::wstring str1 = L"гибралтар", str2 = L"лабрадор.";
        QCOMPARE(Hamming(str1, str2), 6);
        std::string str3 = "example", str4 = "xeomple";
        QCOMPARE(Hamming(str3, str4), 3);
    }
};

QTEST_MAIN(TestHamming)
#include "TestHamming.moc"