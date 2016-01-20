public class WeightedUnionFind {
    int id[];
    int sz[];

    public WeightedUnionFind(int N) {
        id = new int[N];
        sz = new int[N];

        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    private int root(int i) {
        while (i != id[i]) i = id[i];
        return i;
    }

    public boolean connected(int p, int q) {
        return root(p) == root(q);
    }

    public void union(int p, int q) {
        int i = root(p);
        int j = root(q);
        if (i == j) return;
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
    }

    public void print() {
        for (int i = 0; i < id.length; i++) {
            System.out.print(id[i] + " ");
        }
        System.out.print("\n");
    }

    public static void main(String[] args) {
        WeightedUnionFind wuf = new WeightedUnionFind(10);

        wuf.union(8, 4);
        wuf.union(5, 8);
        wuf.union(3, 6);
        wuf.union(1, 0);
        wuf.union(7, 9);
        wuf.union(9, 0);
        wuf.union(3, 5);
        wuf.union(3, 9);
        wuf.union(6, 2);

        wuf.print();
    }
}
