/*
Using instructions:
struct node *root = makenode();
insertword(root, s);
deleteword(root, s);
searchword(root, s); -> boolean
*/


struct node
{
	struct node *daughters[26];
	char ch;
	bool fin;
};

struct node *makenode()
{
	struct node *fnode = new node;
	fnode->fin = 0;
	fnode->ch = '#';
	for(int i = 0; i < 26; i++)
	{
		fnode->daughters[i] = NULL;
	}
	return fnode;
};

void insertword(struct node *root, string s)
{
	struct node *temp = root;
	for(int i = 0; i < s.size(); i++)
	{
		int id = s[i] - 'a';
		if(temp->daughters[id] == NULL)
		{
			temp->daughters[id] = makenode();
			temp->daughters[id]->ch = s[i];
		}
		temp = temp->daughters[id];
	}
	temp->fin = 1;
}

bool searchword(struct node *root, string s)
{
	struct node *temp = root;
	for(int i = 0; i < s.size(); i++)
	{
		int id = s[i] - 'a';
		if(temp->daughters[id] == NULL)
		{
			return false;
		}
		temp = temp->daughters[id];
	}
	if(temp->fin == true && temp != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool del(struct node *cur, string s, int cnt, int length)
{
	if(cur)
	{
		if(cnt == length)
		{
			if(cur->fin)
			{
				cur->fin = 0;
				bool flag = 1;
				for(int i = 0; i < 26; i++)
				{
					if(cur->daughters[i])
					{
						flag = 0;
					}
				}
			}
		}
		else
		{
			int id = s[cnt] - 'a';
			if(del(cur->daughters[id], s, cnt+1, length))
			{
				free(cur->daughters[id]);
				cur->daughters[id] = NULL;
				bool flag = 1;
				for(int i = 0; i < 26; i++)
				{
					if(cur->daughters[i])
					{
						flag = 0;
					}
				}
				return (cur->fin == 0 && flag);
			}
		}
	}
	return 0;
}

void deleteword(struct node *root, string s)
{
	int length = s.size();
	if(length > 0)
	{
		del(root, s, 0, length);
	}
}
