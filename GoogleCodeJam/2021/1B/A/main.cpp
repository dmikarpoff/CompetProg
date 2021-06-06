#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    int t;
    cin >> t;
    constexpr int64_t kTicksInMin = 720000000000;
    constexpr int64_t kTickInClock = static_cast<int64_t>(3600) * static_cast<int64_t>(12000000000);

    for (int o = 1; o <= t; ++o) {
        int64_t a[3];
        cin >> a[0] >> a[1] >> a[2];
        bool found = false;
        int64_t h = 0;
        int64_t m = 0;
        int64_t s = 0;
        int64_t ns = 0;
        constexpr int64_t k12 = 12;
        constexpr int64_t k720 = 720;
        for (int i = 0; i < 3 && !found; ++i) {
            for (int j = 0; j < 3 && !found; ++j) {
                if (i != j) {
                    for (int k = 0; k < 3 && !found; ++k) {
                        if (k != i && k != j) {
                            int64_t h_pos = a[i];
                            int64_t m_pos = a[j];
                            int64_t s_pos = a[k];
                            cout << "h_pos = " << h_pos << endl;
                            cout << "m_pos = " << m_pos << endl;
                            cout << "s_pos = " << s_pos << endl;
                            if (m_pos % k12 != 0) {
                                int64_t rem = k12 - m_pos % k12;
                                h_pos = (h_pos + rem) % kTickInClock;
                                m_pos = (m_pos + rem) % kTickInClock;
                                s_pos = (s_pos + rem) % kTickInClock;
                            }
                            if (s_pos % k720 != 0) {
                                int64_t rem = k720 - s_pos % k720;
                                h_pos = (h_pos + rem) % kTickInClock;
                                m_pos = (m_pos + rem) % kTickInClock;
                                s_pos = (s_pos + rem) % kTickInClock;
                            }
                            cout << "After normalize" << endl;
                            cout << "h_pos = " << h_pos << endl;
                            cout << "m_pos = " << m_pos << endl;
                            h_pos = (h_pos + kTickInClock - s_pos) % kTickInClock;
                            m_pos = (m_pos + kTickInClock - s_pos) % kTickInClock;
                            cout << "After align seconds" << endl;
                            cout << "h_pos = " << h_pos << endl;
                            cout << "m_pos = " << m_pos << endl;
                            if (m_pos % 12 != 0) {
                                cout << "Continue;" << endl;
                                continue;
                            }
                            int64_t ns_since_min = (m_pos % kTicksInMin) / k12;
                            int64_t ns_since_midnight = (h_pos + ns_since_min * k720) % kTickInClock;
                            m_pos = (m_pos + ns_since_midnight * k720) % kTickInClock;
                            cout << "ns_since_midnight = " << ns_since_midnight << endl;
                            constexpr int64_t kNsInHour = static_cast<int64_t>(3600) * static_cast<int64_t>(1000000000);
                            if (m_pos == ns_since_midnight % kNsInHour * static_cast<uint64_t>(12)) {
                                found = true;
                                cout << "Found!!!" << endl;
                                ns = ns_since_midnight % static_cast<int64_t>(1000 * 1000 * 1000);
                                ns_since_midnight /= static_cast<int64_t>(1000 * 1000 * 1000);
                                s = ns_since_midnight % static_cast<int64_t>(60);
                                ns_since_midnight /= static_cast<int64_t>(60);
                                m = ns_since_midnight % static_cast<int64_t>(60);
                                h = ns_since_midnight / static_cast<int64_t>(60);
                            }
                        }
                    }
                }
            }
        }
        cout << "Case #" << o << ": ";
        cout << h << " " << m << " " << s << " " << ns;
        cout << endl;
    }
    return 0;
}
