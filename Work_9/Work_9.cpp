#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

int getIntegerInput(const std::wstring& prompt) {
    int value;
    while (true) {
        std::wcout << prompt;
        std::wcin >> value;

        if (std::wcin.fail()) {
            std::wcin.clear();  // Сбрасываем флаг ошибки
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');  // Очищаем буфер в
            std::wcout << L"Ошибка ввода. Введите число." << std::endl;
        }
        else {
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');  // Очищаем лишние символы в буфере
            break;
        }
    }
    return value;
}

void distributeItems(std::vector<int>& items, int n, int k) {
    std::sort(items.begin(), items.end(), std::greater<int>());

    // Суммарная масса вещей
    int totalWeight = 0;
    for (int i = 0; i < k; ++i) {
        totalWeight += items[i];
    }

    // Создаем массив для хранения результатов динамического программирования
    std::vector<std::vector<bool>> dp(k + 1, std::vector<bool>(totalWeight / 2 + 1, false));

    // Базовый случай: разница масс вещей равна 0
    for (int i = 0; i <= k; ++i) {
        dp[i][0] = true;
    }

    // Динамическое программирование
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= totalWeight / 2; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= items[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - items[i - 1]];
            }
        }
    }

    // Находим самую маленькую разницу
    int minDifference = totalWeight;
    for (int j = totalWeight / 2; j >= 0; --j) {
        if (dp[k][j]) {
            minDifference = totalWeight - 2 * j;
            break;
        }
    }

    // Выводим результат
    std::wcout << L"Самая маленькая разница масс по рюкзакам: " << minDifference << std::endl;

    // Выводим массу по рюкзакам
    std::wcout << L"Масса в рюкзаке 1: " << (totalWeight - minDifference) / 2 << L" кг" << std::endl;
    std::wcout << L"Масса в рюкзаке 2: " << (totalWeight + minDifference) / 2 << L" кг" << std::endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n, k;

    n = getIntegerInput(L"Введите количество рюкзаков: ");
    k = getIntegerInput(L"Введите количество вещей: ");

    std::vector<int> items(k);
    std::wcout << L"Введите массы вещей:" << std::endl;
    for (int i = 0; i < k; ++i) {
        std::wcout << L"Вещь " << (i + 1) << L": ";
        items[i] = getIntegerInput(L"");
    }

    distributeItems(items, n, k);

    return 0;
}
