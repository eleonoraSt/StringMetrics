#include <QTest>

#include "..\include\editDistance.h"

class TestLevenstein: public QObject {
    Q_OBJECT
private slots:
    void identical() {
        std::string str1 = "aaa", str2 = "aaa";
        QCOMPARE(Levenstein(str1, str2), 0);
        std::wstring str3 = L"Հայոց", str4 = L"Հայոց";
        QCOMPARE(Levenstein(str3, str4), 0);
        std::u16string str5 = u"汉字", str6 = u"汉字";
        QCOMPARE(Levenstein(str5, str6), 0);
    }

    void insertion() {
        std::string str1 = "aaa", str2 = "aabca";
        QCOMPARE(Levenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"աՀայոց";
        QCOMPARE(Levenstein(str3, str4), 1);
        std::u16string str5 = u"汉字", str6 = u"汉字字";
        QCOMPARE(Levenstein(str5, str6), 1);
    }

    void deletion() {
        std::string str1 = "abc", str2 = "b";
        QCOMPARE(Levenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հայ";
        QCOMPARE(Levenstein(str3, str4), 2);
        std::u16string str5 = u"汉字", str6 = u"字";
        QCOMPARE(Levenstein(str5, str6), 1);
    }

    void substitution() {
        std::string str1 = "aaa", str2 = "cba";
        QCOMPARE(Levenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հայո!";
        QCOMPARE(Levenstein(str3, str4), 1);
        std::u16string str5 = u"汉字", str6 = u"水字";
        QCOMPARE(Levenstein(str5, str6), 1);
    }

    void transposition() {
        std::string str1 = "abc", str2 = "acb";
        QCOMPARE(Levenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հյաոց";
        QCOMPARE(Levenstein(str3, str4), 2);
        std::u16string str5 = u"汉字", str6 = u"字汉";
        QCOMPARE(Levenstein(str5, str6), 2);
    }

    void mixed() {
        std::string str1 = "гибралтар", str2 = "лабрадор";
        QCOMPARE(Levenstein(str1, str2), 5);
    }
};

QTEST_MAIN(TestLevenstein)
