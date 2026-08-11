#include <QTest>

#include "..\include\editDistance.h"

class TestLCS: public QObject {
    Q_OBJECT
private slots:
    void identical() {
        std::string str1 = "aaa", str2 = "aaa";
        QCOMPARE(Lcs(str1, str2), 3);
        std::wstring str3 = L"Հայոց", str4 = L"Հայոց";
        QCOMPARE(Lcs(str3, str4), 5);
        std::u16string str5 = u"汉字", str6 = u"汉字";
        QCOMPARE(Lcs(str5, str6), 2);
    }

    void insertion() {
        std::string str1 = "aaa", str2 = "aabca";
        QCOMPARE(Lcs(str1, str2), 2);
        std::wstring str3 = L"Հայոց", str4 = L"աՀայոց";
        QCOMPARE(Lcs(str3, str4), 5);
        std::u16string str5 = u"汉字", str6 = u"汉字字";
        QCOMPARE(Lcs(str5, str6), 2);
    }

    void deletion() {
        std::string str1 = "abcd", str2 = "bc";
        QCOMPARE(Lcs(str1, str2), 2);
        std::string str2_5 = "ad";
        QCOMPARE(Lcs(str1, str2_5), 1);
        std::wstring str3 = L"Հայոց", str4 = L"Հայ";
        QCOMPARE(Lcs(str3, str4), 3);
        std::u16string str5 = u"汉字", str6 = u"字";
        QCOMPARE(Lcs(str5, str6), 1);
    }

    void substitution() {
        std::string str1 = "aaa", str2 = "aba";
        QCOMPARE(Lcs(str1, str2), 1);
        std::wstring str3 = L"Հայոց", str4 = L"Հայո!";
        QCOMPARE(Lcs(str3, str4), 4);
        std::u16string str5 = u"汉字", str6 = u"水字";
        QCOMPARE(Lcs(str5, str6), 1);
    }

    void mixed() {
        std::wstring str1 = L"гибралтар", str2 = L"лабрадор";
        QCOMPARE(Levenstein(str1, str2), 3);
        std::string str3 = "example", str4 = "xeomple";
        QCOMPARE(Levenstein(str3, str4), 4);
    }
};

QTEST_MAIN(TestLCS)
#include "TestLCS.moc"