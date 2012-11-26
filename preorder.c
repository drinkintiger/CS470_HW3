BuildTree(argv[1], &root, &nodes, &count,&leftMost);

#pragma omp parallel default(shared) private(i) num_threads(count)
{
    i = omp_get_thread_num();
    if (nodes[i]->sibling == NULL)
    nodes[i]->order = nodes[i]->parent;
}

#pragma omp parallel default(shared) private(i, j, n, d, temp) num_threads(count)
{
    i = omp_get_thread_num();
    temp = nodes[i];
    for (j = 1; j <= count; j = 2*j) {
        if (temp->order != NULL ){
            n = temp->order->order;
            d = temp->post + temp->order->post;
        }
    #pragma omp barrier
    if (temp->order != NULL) {
        temp->post = d;
        temp->order = n;
    }
    #pragma omp barrier
    }
    temp->post = count - temp->post;
}
