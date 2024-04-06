string removeStars(string s) {
    vector<char> temp;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {
            temp.erase(temp.end() - 1);
        } else {
            temp.push_back(s[i]);
        }
    }
    string ans = "";
    for (int i = 0; i < temp.size(); ++i) {
        ans += temp[i];
    }
    return ans;
}