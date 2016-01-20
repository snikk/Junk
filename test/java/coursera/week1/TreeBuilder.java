public class TreeBuilder {
    public static void main(String[] args) {
        int id[] = new int[args.length];
        int sz[] = new int[args.length];
        for (int i = 0; i < args.length; i++) {
            id[i] = Integer.parseInt(args[i]);
            sz[i] = 1;
        }

        for (int i = 0; i < args.length; i++) {
            if (id[i] == i)
                sz[i] = size(id, sz, i);
        }

        System.out.print("Sizes array\n");
        for (int i = 0; i < sz.length; i++) {
            System.out.print(sz[i] + " ");
        }
        System.out.print("\nEnd Sizes array\n");
    }

    public static int size(int[] id, int[] sz, int root) {
        int size = sz[root];
        for (int i = 0; i < id.length; i++) {
            if (i != root && id[i] == root) {
                int itemSize = size(id, sz, i);
                sz[i] = itemSize;
                size += itemSize;
            }
        }

        return size;
    }
}
