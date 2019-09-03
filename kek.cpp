const int NMAX = 100000;
ll a[NMAX];
ll t[4 * NMAX];
ll tAdd[4 * NMAX];

void build(int v, int vl, int vr)
{
	if (vl == vr)
	{
		t[v] = a[vl];
		return;
	}

	int vm = vl + (vr - vl) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm + 1, vr);

	t[v] = t[2 * v + 1] + t[2 * v + 2];
}

void push(int v, int vl, int vr) //выполняем ленивое проталкивание, то есть
{								 // передаем потомкам информацию о добавленном элементе и
								 // пересчитываем значение в вершине
	if (tAdd[v] != 0)
	{
		t[v] += tAdd[v] * ll((vr - vl + 1));
		if (vl != vr) // если есть потомки
		{
			tAdd[2 * v + 1] += tAdd[v];
			tAdd[2 * v + 2] += tAdd[v];
		}
		tAdd[v] = 0;
	}
}

ll query(int v, int vl, int vr, int l, int r)
{
	push(v, vl, vr); // когда мы делаем какое-либо действие с деревом, мы проталкиваем 

	if (r < vl || vr < l)
		return 0;
	if (vl >= l && vr <= r)
		return t[v];

	int vm = vl + (vr - vl) / 2;
	ll ql = query(2 * v + 1, vl, vm, l, r);
	ll qr = query(2 * v + 2, vm + 1, vr, l, r);
	return ql + qr;
}

void modify(int v, int vl, int vr, int l, int r, ll val)
{
	push(v, vl, vr);
	if (r < vl || vr < l)
		return;
	if (vl >= l && vr <= r)
	{
		tAdd[v] = val;
		push(v, vl, vr);
		return;
	}

	int vm = vl + (vr - vl) / 2;
	modify(2 * v + 1, vl, vm, l, r, val);
	modify(2 * v + 2, vm + 1, vr, l, r, val);

	t[v] = t[2 * v + 1] + t[2 * v + 2];
}
