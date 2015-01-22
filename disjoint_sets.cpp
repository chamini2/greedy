class disjoint_sets {
public:
    std::vector<int> _representatives;
    std::vector<int> _ranks;
    std::vector<int> _sizes;
    int _length;

    disjoint_sets();
    ~disjoint_sets();

    disjoint_sets(int size) {
        _representatives.reserve(size);
        _ranks.reserve(size);
        _sizes.reserve(size);
        _length = size;

        this->clear();
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            _representatives[i] = i;
            _ranks[i] = 0;
            _sizes[i] = 1;
        }
    }

    void union(int a, int b) {
        int arep, brep;

        arep = this->find(a);
        brep = this->find(b);

        // If they are on different disjoint sets
        if (arep != brep) {
            if (_ranks[arep] > _ranks[brep]) {
                _representatives[brep] = arep;
                _sizes[arep] += _sizes[brep];

            } else if (_ranks[arep] < _ranks[brep]) {
                _representatives[arep] = brep;
                _sizes[brep] += _sizes[arep];

            } else {
                _representatives[arep] = brep;
                _sizes[brep] += _sizes[arep];
                _ranks[brep]++;
            }
        }
    }

    int find(int id) {
        if (0 <= id && id < length) {
            if (_representatives[id] == id) {
                return id;
            } else {
                _representatives[id] = this->find(_representatives[id]);
                return _representatives[id];
            }
        }
    }
};