// Function.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "math.h"
#include "express.h"
#include <ctype.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




IMPLEMENT_SERIAL(CExpression, CObject, 0)


#define   PI 3.141592653589793


//////////////////////////////////////////////////////////////////////
// CExpression Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Variabile Globale


/////////////////////////////////////////////////////////////////////////////////
// Eliberarea memorie ocupate de arbore

void CExpression::elibmem ( arbore a)
{
if (a==NULL) return;
if (a->left!=NULL) elibmem(a->left);
if (a->right!=NULL) elibmem(a->right);
if (a->operatie == '`')
		delete a->valoarestr;
delete a;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpression::CExpression()
{
	m_Arbore = NULL;
	m_definitie = "";
	pozitie = 0;
	m_pvariabile = NULL;

	m_identifyx=0;
	m_xvalue=0;
}

CExpression::CExpression(CMapVariabile * vars)
{
	m_Arbore = NULL;
	m_definitie = "";
	pozitie = 0;
	m_pvariabile = vars;
}

CExpression::~CExpression()
{
 elibmem (m_Arbore);
}

void CExpression::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_definitie;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_definitie;
		m_Arbore = NULL;
		pozitie = 0;
		UpdateArbore();
		// After loading this object if it contains variables you should attach a variable 
		// Table to it
	}
}


int CExpression::UpdateArbore()
{
	if (m_definitie.IsEmpty())
		return 0;
	elibmem(m_Arbore); // Eliberarea memoriei ocupate de arbore
	m_Arbore = NULL;
	pozitie = 0;
	m_Arbore = expresie();
	if (m_definitie[pozitie]!='\0') 
	{
		elibmem(m_Arbore);
		m_Arbore = NULL;
	}

	if (m_Arbore == NULL)
		return pozitie;
	else return -1;
}

CExpression::arbore CExpression::expresie()
{
	arbore nod;
	arbore arb1 = termen();
	arbore arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate

	

	while ((m_definitie[pozitie]=='-') || (m_definitie[pozitie]=='+')) 
	{
		nod=new NOD;
		nod->left=arb1;
		nod->operatie=m_definitie[pozitie];
		pozitie++;
		arb2 = termen();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			elibmem(nod);
			return NULL;  // In caz de eroare terminate
		}
		arb1 = nod;
	}
	return arb1;
}


CExpression::arbore CExpression::commatose() //factor comma
{

   arbore nod = NULL,nod2 = NULL,left = NULL;
   while(m_definitie[pozitie] == ' ' && m_definitie[pozitie] != '\0')
	 pozitie++;

 //only allows open braket
 if (m_definitie[pozitie]=='(')
    {
      pozitie++;
      nod = expresie();
      if (nod == NULL) return NULL;
	  if (m_definitie[pozitie]!=',')
	  {
		elibmem(nod);
		return NULL;
	  }
	  //pozitie++;
	  return nod;
    }
 else return NULL;
 
 // else return identificator();
 //return nod;


}


CExpression::arbore CExpression::commaend() //factor comma
{

   arbore nod = NULL,nod2 = NULL,left = NULL;
   while(m_definitie[pozitie] == ' ' && m_definitie[pozitie] != '\0')
	 pozitie++;

 //only allows open comma
 if (m_definitie[pozitie]==',')
    {
      pozitie++;
      nod = expresie();
      if (nod == NULL) return NULL;
	  if (m_definitie[pozitie]!=')')
	  {
		elibmem(nod);
		return NULL;
	  }
	  pozitie++;
	  return nod;
    }
 else return NULL;
 
 //else return identificator();
 //return nod;


}



CExpression::arbore CExpression::termen()
{
	arbore nod;
	arbore arb1 = putere();
	arbore arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate

	

	while ((m_definitie[pozitie]=='*') || (m_definitie[pozitie]=='/')) 
	{
		nod=new NOD;
		nod->left=arb1;
		nod->operatie=m_definitie[pozitie];
		pozitie++;
		arb2 = putere();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			elibmem(nod);
			return NULL;  // In caz de eroare terminate
		}
		arb1 = nod;
	}
	return arb1;
}



CExpression::arbore CExpression::putere() //to the power of
{
	arbore nod = NULL;
	arbore arb1 = logicalOp();
	arbore arb2;
	if  (arb1 == NULL) return NULL;  // In caz de eroare terminate
	

	while (m_definitie[pozitie]=='^') 
	{
		nod=new NOD;
		nod->left=arb1;
		nod->operatie=m_definitie[pozitie];
		pozitie++;
		arb2 = logicalOp();
		nod->right=arb2;
		if  (arb2 == NULL) 
		{
			elibmem(nod);
			return NULL;  // In caz de eroare terminate
		}
		arb1 = nod;
	}
	return arb1;
}


CExpression::arbore CExpression::factor()
{


 arbore nod = NULL,nod2 = NULL,left = NULL,parent=NULL;
 while(m_definitie[pozitie] == ' ' && m_definitie[pozitie] != '\0')
	 pozitie++;

 
 //during factoring , there are two cases:
 //1)brackets
 //2)identificator


  //skip unary +
  if (m_definitie[pozitie]=='+')
  {
     pozitie++;
  }
 
  BOOL unary=FALSE;
  //modify tree for unary -
 if (m_definitie[pozitie]=='-')
   {
    parent = new NOD;
    left = new NOD;
    left->right=NULL;
    left->left=NULL;
    left->operatie=168;
    left->valoare=-1;
	parent->left=left;
    parent->operatie='*';
    pozitie++;
	unary=TRUE;

	//parent->right = expresie();
	//if (parent->right == NULL) return NULL;
	//return parent;   
 }
 
 
 if (m_definitie[pozitie]=='(')
    {
      pozitie++;
      nod = expresie();
	  //TRACE("\nResumed here %c",m_definitie[pozitie]);
      if (nod == NULL) return NULL;
	  if (m_definitie[pozitie]!=')')
	  {
		//TRACE("\nNULL returned");
		elibmem(nod);
		return NULL;
	  }
	  pozitie++;
	  //return nod;
    }
 else {
	 nod= identificator();
 }


 if (unary) {

	if (parent==NULL) return NULL;
	parent->right = nod;
	if (parent->right == NULL) return NULL;
	return parent;   

 }	
 else
	return nod;

}

CExpression::arbore CExpression::identificator()
{
	int poz;
	arbore nod = NULL,nod2 = NULL,nod3=NULL;
	arbore result = NULL;
	poz=pozitie;
	SkipSpaces();
	if (m_definitie[pozitie]=='\0') result  = NULL;


	
	{

		int state=0;	
		while  ((isdigit(m_definitie[pozitie]) || (m_definitie[pozitie]=='.'))) {

					 
					 if (m_definitie[pozitie]=='.') {
						 state=1;
						 pozitie++;
						 break;
					 }
					 pozitie++;
		}

		if (state==1) {

			while  (isdigit(m_definitie[pozitie])) 
				pozitie++;

		}

		//TRACE("\npoz=%d ",poz);
		//TRACE("pozities=%d ",pozitie);
		//TRACE("char=%c",m_definitie[poz]);
		if (((pozitie-poz)==1) && (m_definitie[poz]=='.')) 
		{

			//TRACE(". on");
			pozitie--;

		}
		else if (pozitie>poz) {
			nod = new NOD;
			nod->left = NULL; 
			nod->right = NULL;
			nod->operatie = 168;
			nod->valoare = atof(m_definitie.Mid(poz,pozitie-poz));
			result = nod;
		}
	
	}



	if (isalpha(m_definitie[pozitie]))	// Am i an identifier ?
	{
		while  (isalnum(m_definitie[pozitie])) 
				pozitie++;
			
		

		CString id = m_definitie.Mid(poz,pozitie-poz);
		CString nid = id;
		id.MakeUpper();

		if (id =="SIN")		// Functia sinus CString
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=150;
			SkipSpaces();
			return nod;
		}
		else if (id =="COS")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=151;
			SkipSpaces();
			return nod;
		}
		else if (id =="EXP")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=152;
			SkipSpaces();
			return nod;
		}
		else if (id =="SQRT")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=153;
			SkipSpaces();
			return  nod;
		}
		else if (id =="LN")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=154;
			SkipSpaces();
			return nod;
		}
		else if (id =="TAN")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=155;
			SkipSpaces();
			return nod;
		}
		/*
		else if (id =="COT")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=156;
			SkipSpaces();
			return nod;
		}
		*/
		else if (id =="ASIN")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=157;
			SkipSpaces();
			return nod;
		}
		else if (id =="ACOS")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=158;
			SkipSpaces();
			return nod;
		}
		else if (id =="ATAN")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=159;
			SkipSpaces();
			return nod;
		}
		else if (id =="ABS")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=160;
			SkipSpaces();
			return nod;
		}
		else if (id =="SINH")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=161;
			SkipSpaces();
			return nod;
		}
		else if (id =="COSH")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=162;
			SkipSpaces();
			return nod;
		}
		else if (id =="TANH")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=163;
			SkipSpaces();
			return nod;
		}
		else if (id =="LOG10")		
		{
			
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=164;
			SkipSpaces();
			return nod;
		}
		else if (id =="SQR")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=165;
			SkipSpaces();
			return nod;
		}
		else if (id =="DEG2RAD")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=166;
			SkipSpaces();
			return nod;
		}
		else if (id =="RAD2DEG")		
		{
			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=167;
			SkipSpaces();
			return nod;
		}
		else if (id =="ROOT")		
		{
			nod2 = commatose();
			nod3 = commaend();
			nod = new NOD;
			nod->left = nod2;
			nod->right=nod3;
			nod->operatie=170;
			SkipSpaces();
			return nod;
		}
		else if (id =="LOG")		
		{
			nod2 = commatose();
			nod3 = commaend();
			nod = new NOD;
			nod->left = nod2;
			nod->right=nod3;
			nod->operatie=171;
			SkipSpaces();
			return nod;
		}
		else if (id =="DIV")		
		{
			nod2 = commatose();
			nod3 = commaend();
			nod = new NOD;
			nod->left = nod2;
			nod->right=nod3;
			nod->operatie=172;
			SkipSpaces();
			return nod;
		}
		else if (id =="REMAINDER")		
		{
			nod2 = commatose();
			nod3 = commaend();
			nod = new NOD;
			nod->left = nod2;
			nod->right=nod3;
			nod->operatie=173;
			SkipSpaces();
			return nod;
		}
		else if (id =="FACT")		
		{

			nod2 = factor();
			nod = new NOD;
			nod->left = nod2;
			nod->right=NULL;
			nod->operatie=175;
			nod->subfunction=0;
			SkipSpaces();
			return nod;
		}
		else if (id =="NPR")		
		{
			nod2 = commatose();
			nod3 = commaend();
			nod = new NOD;
			nod->left = nod2;
			nod->right=nod3;
			nod->operatie=175;
			nod->subfunction=1;
			SkipSpaces();
			return nod;
		}
		else if (id =="NCR")		
		{

			nod2 = commatose();
			nod3 = commaend();
			nod = new NOD;
			nod->left = nod2;
			nod->right=nod3;
			nod->operatie=175;
			nod->subfunction=2;
			SkipSpaces();
			return nod;
		}

		//indentify variable x here 
		if (m_identifyx) {
			if ((nid=="x") || (nid=="X")) {

				nod = new NOD;
				nod->right=NULL;
				nod->left=NULL;
				nod->operatie=168;
				nod->valoare=m_xvalue;
				SkipSpaces();
				return nod;
			}
		}
		



		CValue *valoare;
		if (m_pvariabile->Lookup(nid,valoare))
		{
			nod = new NOD;
			nod -> left = NULL;
			nod -> right = NULL;
			nod -> operatie = '`';
			nod -> valoarestr = new CString(nid); 
			result = nod;
		}
		else 
			result = NULL;
	}
	SkipSpaces();
	return result;
        
}

int CExpression::ChangeExpression(CString & expresie)
{
	m_definitie = expresie + '\0' + '\0';
	
	return UpdateArbore();
}


// Error code var
// put into a member object
int CExpression::Value(double& valoare)
{
  code=0;
  errorstatus=0;
  if (m_Arbore == NULL) return -1;
  valoare=vexp(m_Arbore);
  return (code);
}


double CExpression::vexp ( arbore a )
{
double v;


if (a==NULL) {
	errorstatus=1;
	code=ERROR_CODE;
	return 0;
}
	

if (a->operatie==NULL) {code=10;return 0;}
switch(a->operatie) 
 {
 case '+' : return( vexp(a->left)+vexp(a->right) );
 case '-' : return( vexp(a->left)-vexp(a->right) );
 case '*' : return( vexp(a->left)*vexp(a->right) );
 case '/' : { v=vexp(a->right) ;
			 if (v==0)
			 {code=DIVISION_BY_0;return -vexp(a->left)/0.001;}
			 else
				return(vexp(a->left)/v);
			}
 case 150 : return(sin(vexp(a->left))); 
 case 151 : return(cos(vexp(a->left)));
 case 152 : return(exp(vexp(a->left)));
 case 153 : { 
			 v=vexp(a->left) ;
			 if (v<0) {code=UNKNOWN_ROOT;return 0;}
			 else return(sqrt(v));
			}
 case 154 : {
			 v=vexp(a->left) ;
			 if (v<=0) {code=UNKNOWN_ROOT;return 0;}
			 else return(log(v));
			}
 case 155 : return (tan (vexp(a->left)));
 case 156 : return (1 / tan (vexp(a->left)));
 case 157 : {
				if (fabs( vexp(a->left) )>1) {code=UNKNOWN_ROOT;return 0;}
				return (asin (vexp(a->left)));
			}
 case 158 : {
				if (fabs( vexp(a->left) )>1) {code=UNKNOWN_ROOT;return 0;}
				return (acos (vexp(a->left)));
			}
 case 159 : return (atan (vexp(a->left)));
 case 160 : return (fabs (vexp(a->left)));  
 case 161 : return (sinh (vexp(a->left)));
 case 162 : return (cosh (vexp(a->left))); 
 case 163 : return (tanh (vexp(a->left)));
 case 164 : {
				if (vexp(a->left)<=0) {
					code=UNKNOWN_ROOT;
					return 0;
				}
				return (log10 (vexp(a->left)));
			}	
 case 165 : return ((vexp(a->left))*(vexp(a->left)));
 case 166 : return ((vexp(a->left)*PI)/180.0); 
 case 167 : return ((vexp(a->left)*180.0)/PI); //upto here range of arugment is ok! checked
 //case '|' : return(fabs(vexp(a->left)));
 case '^' : {
	 
				//ok 
				//still need to check for fractional...i.e root
				//the raise to interger power constraints...solve it...
				double rright=vexp(a->right);
				if (vexp(a->left)==0 && vexp(a->right)==0) {code=UNKNOWN_ROOT;return 0;}
				if (vexp(a->left)==0. && vexp(a->right)<0) {code=UNKNOWN_ROOT;return 0;}
					//return(eerror("Cannot raise zero to a negative power."));
				if (vexp(a->left)<0 && rright!=((int)rright)) {code=UNKNOWN_ROOT;return 0;}
					//return(eerror("Cannot raise a negative number to a non-integer power."));
				return(pow(vexp(a->left),vexp(a->right))); 

			}
 case 168 : return (a->valoare);
 case 170 : { //root
				//double dx,cx;
				double ax=0;
				double rbase=vexp(a->right);
				double rval=vexp(a->left);

				if (rbase==0) {
					code=UNKNOWN_ROOT;
					return 0;
				}
				else if ((rval==0) && (rbase<0)) {
					code=UNKNOWN_ROOT;
					return 0;
				}

				if (rval<0) { //number is negative
					if ((remainder(rbase,2.0)==1) || (remainder(rbase,2.0)==-1)) {
					//if (remainder(rbase,2.0)==1) {
						//if root is integer and odd
						//must be divisible by 2==>integer
						//remainder must be 1 or -1==>odd
						rval=-rval;
						ax=pow(rval,1/rbase);
						ax=-ax;
					}
				}
				else {
				
					//TRACE("This get run");
					ax=(pow(vexp(a->left),1/vexp(a->right)));

				}

				

				if ((fabs(ax)<0.0000000000000000001) && (vexp(a->left)!=0)) {
					code=UNKNOWN_ROOT;
					return 0;
				}

				//TRACE("\n%f %f %f",dx,ax,cx);
				return ax;
			}
 case 171 :  {   //log(a,b)
				
				//not sure
				if ((vexp(a->left)>0) && (vexp(a->right)>0))
					return (log10(vexp(a->left))/log10(vexp(a->right)));
				else if ((vexp(a->left)<=0) && (vexp(a->right)>=0)) {
					code=UNKNOWN_ROOT;
					return 0;
				}
				else if (vexp(a->left)==1) {
					return 0;
				}
				else if ((vexp(a->left)!=0) && (vexp(a->right)==0)) {//at this point imply that : left must be greater than 0 due to the 1st if statement above
					code=UNKNOWN_ROOT;
					return 0;
				}
				else if ((vexp(a->left)>=0) && (vexp(a->right)<0)) { //for neg base, can only allows integral powers to be returned
					double dx=log10(vexp(a->left))/log10(-vexp(a->right));
					if ((dx>0) && (remainder(dx,2)==0.0)) {//if integer and even
						
						//q: need to check dx is positive?
						return dx; // a positive value is returned..q: can a neg value be returned?
					}
					else {
						code=UNKNOWN_ROOT;
						return 0;
						
					}
				}
				else if ((vexp(a->left)<0) && (vexp(a->right)<0)) {
					double dx=log10(-vexp(a->left))/log10(-vexp(a->right));
					if ((dx>0) && (remainder(dx,2)==1.0)) {//if integer and odd
						return dx;
					}
					else {
						code=UNKNOWN_ROOT;
						return 0;
						
					}
				}
				else {
					code=UNKNOWN_ROOT;
					return 0;
				}

			 }
 case 172 : return (int(vexp(a->left)/vexp(a->right)));
 case 173 : { //remainder
				double divx=vexp(a->right);
				double quotient=int(vexp(a->left)/divx);
				double b=quotient*divx;
				return (vexp(a->left)-b);

			}	
 case 175 : { //many braches here:

				 if ((a->subfunction)==0) { //factorial

					 double ve=vexp(a->left);

					 if (ve<0) { //if < 0
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else if (ve!=((int)ve))
					 { //if not int
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else if (ve<2) {

						 return 1;

					 }
					 else {

						 double i;
						 double result=1;
						 for (i=1.0; i<=ve;i++) {
							 result*=i;
						 }
						 return result;

					 }
				 }			
				 else if ((a->subfunction)==1) { //permutation 


					 double ve=vexp(a->left);
					 double vr=vexp(a->right);
					 
					 if (ve<0) { //if < 0
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else if (ve!=((int)ve))
					 { //if not int
						code=UNKNOWN_ROOT;
						return 0;
					 }

					 if (vr<0) { //if < 0
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else if (vr!=((int)vr))
					 { //if not int
						code=UNKNOWN_ROOT;
						return 0;
					 }

					 if (vr>ve) {
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else {

 						 double i;
						 double result=1;
						 double x=ve-vr;
						 for (i=ve; i>x;i--) {
							 result*=i;
						 }
						 return result;


					 }

				 }
				 else if ((a->subfunction)==2) { //combination


					 double ve=vexp(a->left);
					 double vr=vexp(a->right);
					 
					 if (ve<0) { //if < 0
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else if (ve!=((int)ve))
					 { //if not int
						code=UNKNOWN_ROOT;
						return 0;
					 }

					 if (vr<0) { //if < 0
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else if (vr!=((int)vr))
					 { //if not int
						code=UNKNOWN_ROOT;
						return 0;
					 }

					 if (vr>ve) {
						code=UNKNOWN_ROOT;
						return 0;
					 }
					 else {

 						 double i;
						 double result=1;
						 double x=ve-vr;
						 for (i=ve; i>x;i--) {
							 result*=i;
						 }
						 result/=factorial(vr);
						 return result;


					 }

				 }	
 				 else {
					code=UNKNOWN_ROOT;
					return 0;
				 }

			}
	
 
 default  : {
				if (m_pvariabile==NULL) 
				{
					code=UNDEFINED_VARIABLE;
					return 0;
				}
				CValue *valoare;
				if (!m_pvariabile->Lookup(*a->valoarestr,valoare))
				{
					code=UNDEFINED_VARIABLE;
					return 0;
				}
				else 
				return valoare->GetValue();
			}
 }
}


CExpression::arbore CExpression::GetArbore()
{
	return m_Arbore;
}


CExpression::CExpression(CExpression & expresie)
{
	*this = expresie;
}




CExpression::arbore CExpression::CloneTree()
{
	return clone(m_Arbore);	
}

void CExpression::AtachVariables(CMapVariabile * vars)
{
	m_pvariabile = vars;
}

CExpression::arbore CExpression::clone(arbore arb)
{
	if (arb == NULL)
		return NULL;
	arbore clonArb = new NOD;
	*clonArb = *arb;
	clonArb->left = clone(arb->left);
	clonArb->right = clone(arb->right);
	return clonArb;
}

CExpression& CExpression::operator=(CExpression &expr)
{
	m_definitie = expr.m_definitie;
	m_pvariabile = expr.m_pvariabile;
	pozitie = 0;
	m_Arbore = expr.CloneTree();
	return *this;
}

void CExpression::SkipSpaces()
{
	while (m_definitie[pozitie]==' ' && m_definitie[pozitie]!='\0')
		pozitie ++;
}



CExpression::arbore CExpression::logicalOp()
{

	arbore arb1 = sgOp();
		
	return arb1;
}


CExpression::arbore CExpression::sgOp()
{
	arbore nod = NULL;
	nod = factor();	
	return nod;
}



double CExpression::remainder(double left,double right)
{

	double divx=right;
	double quotient=int(left/divx);
	double b=quotient*divx;
	return (left-b);

}

double CExpression::factorial(double x)
{

		 if (x<2) {

			 return 1;

		 }
		 else {

			 double i;
			 double result=1;
			 for (i=1.0; i<=x;i++) {
				 result*=i;
			 }
			 return result;

		 }

}
