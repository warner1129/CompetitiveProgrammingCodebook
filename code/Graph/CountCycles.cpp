// ord = sort by deg decreasing, rk[ord[i]] = i
// D[i] = edge point from rk small to rk big
for (int x : ord) { // c3
  for (int y : D[x]) vis[y] = 1;
  for (int y : D[x]) for (int z : D[y]) c3 += vis[z];
  for (int y : D[x]) vis[y] = 0;
}
for (int x : ord) { // c4
  for (int y : D[x]) for (int z : adj[y])
    if (rk[z] > rk[x]) c4 += vis[z]++;
  for (int y : D[x]) for (int z : adj[y])
    if (rk[z] > rk[x]) --vis[z];
} // both are O(M*sqrt(M)), test @ 2022 CCPC guangzhou
