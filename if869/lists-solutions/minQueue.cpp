#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define br cout << "\n"
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);

ll A = 1664525, C = 1013904223, R = pow(2, 32), seed, rnd;


ll pRand(){
    rnd = (ll)((A * rnd + C) % R);
    return rnd;
}

template <typename T>
class MinQueue
{
public:
    queue<T> q;
    vector<T> m;
    vector<int> pos;
    int pushCnt = 0;
    int popCnt = 0;

    MinQueue() {}
    int size() { return (int)q.size(); }
    int size_min() { return (int)m.size(); }

    T min() { return m[0]; }
    int minPos(){
        return pos[0] - popCnt;
    }


    void enqueue(const T &el)
    {
        pushCnt++;
        q.push(el);
        int idx = lower_bound(m.begin(), m.end(), el) - m.begin();
        m.erase(m.begin() + idx, m.end());
        pos.erase(pos.begin() + idx, pos.end());
        m.push_back(el);
        pos.push_back(pushCnt-1);
    }

    T dequeue()
    {
        popCnt++;
        T el = q.front();
        q.pop();
        if (m[0] == el){
            m.erase(m.begin());
            pos.erase(pos.begin());
        }
        return el;
    }
};

int main()
{
    io;
    MinQueue<ll> mq = MinQueue<ll>();
    vector<ll> nums;
    int b,n,p;
    cin >> seed >> b >> n >> p;
    rnd = seed;
    mq.enqueue(seed);
    for (int i = 1; i < b; i++)
    {
        mq.enqueue(pRand());
    }

    for (int i = 0; i < n; i++)
    {
        ll newRand = pRand();
        if (newRand % 10 < p)
        {
            mq.enqueue(pRand());
        }
        else
        {
            mq.dequeue();
        }
        cout << mq.size_min() << " " << mq.minPos(); br;
    }
}