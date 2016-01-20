public class BinaryHeap<T extends Comparable<T>> {
    private T[] heap;
    private int N;

    public BinaryHeap() {
        heap = (T[]) new Comparable[16];
        for (int i = 0; i < heap.length; i++) {
            heap[0] = null;
        }

        N = 0;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (T item : heap)
            sb.append(item + " | ");

        for (int i = 0; 1 << i < heap.length; i++) {
            for (int j = 1 << i; j < 1 << (i + 1) && j <= N; j++) {
                System.out.print(heap[j] + " | ");
            }
            System.out.print('\n');
        }

        return sb.toString();
    }

    public void insert(T item) {
        if (N + 1 == heap.length)
            increaseArray();
        heap[++N] = item;
        swim(N);
    }

    public T delMax() {
        T item = heap[1];
        exch(N, 1);
        N--;
        sink(1);

        if (N < heap.length / 4)
            decreaseArray();

        return item;
    }

    private void exch(int idx1, int idx2) {
        T tmp = heap[idx1];
        heap[idx1] = heap[idx2];
        heap[idx2] = tmp;
    }

    private void sink(int idx) {
        int j;
        while ((j = idx * 2) <= N) {
            //System.out.println("J compare | heap[" + j + "] = " + heap[j] + " | heap[" + (j + 1) + "] = " + heap[j + 1] + " | N = " + N + " | comp = " + (heap[j].compareTo(heap[j + 1])));
            if (j < N && heap[j].compareTo(heap[j + 1]) < 0) j++;
            //System.out.println("idx compare | heap[" + idx + "] = " + heap[idx] + " | heap[" + j + "] = " + heap[j] + " | N = " + N + " | comp = " + (heap[idx].compareTo(heap[j])));
            if (heap[idx].compareTo(heap[j]) > 0) break; 
            exch(idx, j);
            idx = j;
        }
    }

    private void swim(int idx) {
        while (idx > 1) {
            int j = idx / 2;
            if (heap[idx].compareTo(heap[j]) < 0) break; 
            exch(idx, j);
            idx = j;
        }
    }

    private void increaseArray() {
        T[] arr = (T[]) new Comparable[heap.length * 2];
        for (int i = 0; i <= N; i++)
            arr[i] = heap[i];

        heap = arr;
        System.out.println("Increase Array | heap.length = " + heap.length);
    }

    private void decreaseArray() {
        if (heap.length <= 16)
            return;

        T[] arr = (T[]) new Comparable[heap.length / 2];
        for (int i = 0; i <= N; i++)
            arr[i] = heap[i];

        heap = arr;
        System.out.println("Decrease Array | heap.length = " + heap.length);
    }

    public static void main(String[] args) {
        System.out.println("Hey hey hey.");
        BinaryHeap<Integer> heap = new BinaryHeap<Integer>();
        System.out.println(heap.toString());
        

        double chance = 1.0;
        int maxLength = Integer.MIN_VALUE;
        for (int i = 0; i < 100000000; i++) {
            double rnd = Math.random();
            if (rnd < chance) {
                heap.insert((int) (Math.random() * (double) Integer.MAX_VALUE));
                chance -= 0.01;
            } else if (!heap.isEmpty()) {
                heap.delMax();
                chance += 0.01;
            } else {
                chance = 1.0;
            }

            if (heap.size() > maxLength) {
                maxLength = heap.size();
                System.out.println("Max Heap = " + maxLength);
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!heap.isEmpty()) {
            sb.append(heap.delMax() + " | ");
        }
        System.out.println(sb.toString());
    }
}
