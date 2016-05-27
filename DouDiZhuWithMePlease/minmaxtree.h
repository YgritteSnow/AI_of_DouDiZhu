#ifndef __F__MYPROJECTS_DOUDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__
#define __F__MYPROJECTS_DOUDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__

/************************************************************************/
/* ֻѰ�ҿ��Եõ����ߵ�һ�ַ��������������֦���ٴ���                   */
/* �������������ֻ���ӽڵ㲻���ٽڵ㣬�ɽڵ��Լ��ͷ��Լ��ͺ���			*/
/************************************************************************/

#include <deque>
#include <vector>

// �����С�� - �ڵ�
class MinMaxTreeNodeBase
{
public:
	MinMaxTreeNodeBase() :m_father(NULL) {};
	virtual ~MinMaxTreeNodeBase(){
		for( auto it = m_vec_children.begin(); it != m_vec_children.end(); ++it ) { delete (*it); }
		m_vec_children.clear();
	};

	void AddChildren( MinMaxTreeNodeBase* p_children ){
		m_vec_children.push_back( p_children );
		p_children->SetFather( this );
	}
	void SetFather( MinMaxTreeNodeBase* p_father ){ m_father = p_father; }
	std::vector< MinMaxTreeNodeBase* >::iterator FirstChild(){ return m_vec_children.begin(); }
	std::vector< MinMaxTreeNodeBase* >::iterator LastChild(){ return m_vec_children.end(); }

	virtual void Print() = 0;
	virtual void GenerateChildren() = 0;
	virtual bool isUseful(){ return m_curIsMax; }
	virtual bool isAlreadyMinMax(){ return m_isNeedAllMax == m_curIsMax;} // ��Ϊ����� isNeed �Ƕ��Լ��ĺ��Ӷ��ԣ����Դ˴����Լ����෴�ģ�����Ӧ������ȡ�

	bool m_isNeedAllMax;
	bool m_curIsMax;

protected:
	std::vector< MinMaxTreeNodeBase* > m_vec_children;
	MinMaxTreeNodeBase* m_father;

};

// �����С�� - ����
template < typename TreeNode >
class MinMaxTree
{
public:
	typedef TreeNode* TreeNodePtr;
	MinMaxTree():m_root(NULL){}
	virtual ~MinMaxTree(){
		delete m_root;
		m_root = NULL;
	}

	void AddNode( TreeNodePtr father, TreeNodePtr children ){
		father->AddChildren( children );
	}

protected:
	TreeNodePtr m_root;
};

template < typename TreeNode >
class DecidingTree : public MinMaxTree< TreeNode >
{
public:
	DecidingTree(){};
	virtual ~DecidingTree(){};

	void StartGenerate(){
		m_root->GenerateChildren();
	}

	void Print(){
		std::deque< MinMaxTreeNodeBase* > temp_stack;
		temp_stack.push_back( m_root );

		while( !temp_stack.empty() )
		{
			MinMaxTreeNodeBase* cur_node = temp_stack.front();
			temp_stack.pop_front();

			if( !cur_node->isUseful() )
			{
				continue;
			}

			cur_node->Print();
			for( auto it = cur_node->FirstChild(); it != cur_node->LastChild(); ++it )
			{
				if( (*it)->isUseful() )
				{
					temp_stack.push_back( (*it) );
					break;
				}
			}
		}
	}
};

#endif 