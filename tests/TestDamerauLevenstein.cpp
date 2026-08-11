#include <QTest>

#include "..\include\editDistance.h"

class TestDamerauLevenstein: public QObject {
    Q_OBJECT
private slots:
    void identical() {
        std::string str1 = "aaa", str2 = "aaa";
        QCOMPARE(DamerauLevenstein(str1, str2), 0);
        std::wstring str3 = L"Հայոց", str4 = L"Հայոց";
        QCOMPARE(DamerauLevenstein(str3, str4), 0);
        std::u16string str5 = u"汉字", str6 = u"汉字";
        QCOMPARE(DamerauLevenstein(str5, str6), 0);
    }

    void insertion() {
        std::string str1 = "aaa", str2 = "aabca";
        QCOMPARE(DamerauLevenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"աՀայոց";
        QCOMPARE(DamerauLevenstein(str3, str4), 1);
        std::u16string str5 = u"汉字", str6 = u"汉字字";
        QCOMPARE(DamerauLevenstein(str5, str6), 1);
    }

    void deletion() {
        std::string str1 = "abc", str2 = "b";
        QCOMPARE(DamerauLevenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հայ";
        QCOMPARE(DamerauLevenstein(str3, str4), 2);
        std::u16string str5 = u"汉字", str6 = u"字";
        QCOMPARE(DamerauLevenstein(str5, str6), 1);
    }

    void substitution() {
        std::string str1 = "aaa", str2 = "cba";
        QCOMPARE(DamerauLevenstein(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"Հայո!";
        QCOMPARE(DamerauLevenstein(str3, str4), 1);
        std::u16string str5 = u"汉字", str6 = u"水字";
        QCOMPARE(DamerauLevenstein(str5, str6), 1);
    }

    void transposition() {
        std::string str1 = "abc", str2 = "acb";
        QCOMPARE(DamerauLevenstein(str1, str2), 1);
        std::wstring str3 = L"Հայոց", str4 = L"Հյաոց";
        QCOMPARE(DamerauLevenstein(str3, str4), 1);
        std::u16string str5 = u"汉字", str6 = u"字汉";
        QCOMPARE(DamerauLevenstein(str5, str6), 1);
    }

    void mixed() {
        std::wstring str1 = L"гибралтар", str2 = L"лабрадор";
        QCOMPARE(DamerauLevenstein(str1, str2), 5);
    }
};

QTEST_MAIN(TestDamerauLevenstein);
#include "TestDamerauLevenstein.moc"