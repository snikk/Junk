public class UnionFind {
    private int ids[];

    public UnionFind(int N) {
        ids = new int[N];
        for (int i = 0; i < N; i++)
            ids[i] = i;
    }

    public boolean connected(int p, int q) {
        return ids[p] == ids[q];
    }

    public void union(int p, int q) {
        int idP = ids[p];
        int idQ = ids[q];
        for (int i = 0; i < ids.length; i++) {
            if (ids[i] == idP) ids[i] = idQ;
        }
    }

    public void print() {
        for (int i = 0; i < ids.length; i++) {
            System.out.print(ids[i] + " ");
        }
        System.out.print("\n");
    }

    public static void main(String[] args) {
        System.out.println("Hello, World");

        UnionFind uf = new UnionFind(10);

        uf.union(2, 9);
        uf.union(5, 8);
        uf.union(2, 6);
        uf.union(0, 2);
        uf.union(7, 0);
        uf.union(2, 3);

        uf.print();
    }
}
