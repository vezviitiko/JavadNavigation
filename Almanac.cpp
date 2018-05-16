#include "model.h"
//#include "cmath"

CCartesian ModelAlmDec(CAlmanac alm)
{
	CCartesian car;
	
	//1. вычисление большой полуоси
	
	double v = -alm.w;
	double i = alm.icp+alm.di;
	double Tdr = alm.Tcp + alm.dT;
	double p, Tock;
	double a = (double) pow((double) pow((Tdr/(2.0*PI)),2.0)*alm.ny,1.0/3.0);
	RDUMP(a);
	double a1;
	for (int ix = 0; ix < 3; ix++){
		
		p = a*(1.0-pow(alm.e,2.0));
		a1 = a;
		Tock = Tdr * ( 1.0+(3.0/2.0)*alm.C*pow((alm.ae/p),2.0)*((2.0-(5.0/2.0)*pow(sin(i),2.0))*
		(pow((1-pow(alm.e,2.0)),(3.0/2.0))/pow((1+alm.e*cos(alm.w)),2.0))
		+ (pow((1+alm.e*cos(v)),3.0)/(1.0-pow(alm.e,2.0))) ) );
		
		a = pow(pow((Tock/(2.0*PI)),2.0)*alm.ny,(1.0/3.0));
	}	// реализовано вместо mod(a(3)-a(2))<pow(10,-3) == for (int ix = 0; ix < 3; ix++)
		
	//2. Рассчёт момента прохождения восходящего узла орбиты на витке,
	// к которому принадлежит  момент, и долготы восходящего узла на этом витке	
	// вычисление ближайшего високосного года
	int year = alm.year;

	while (year%4 ||(year%100==0 && year%400)){
		year = year - 1;
	}
	RDUMP(year);
	// календарный номер суток внутри четырехлетнего периода от начала ближайшего високосного года
	// по альманаху
	float Na = Date(alm.yearAlm,alm.monthAlm,alm.dayAlm) - Date(year,1,1);
	RDUMP(Na);
	// по данным
	float N0 = Date(alm.year,alm.month,alm.day) - Date(year,1,1);
	RDUMP(N0);
	
	/* истинное звёздное время - используется среднне 
	http://www.astrolib.ru/files/6/Duboshin-Sprav_Ruk_po_Neb_Meh.pdf
	стр 159
	*/
	double t = dateTojd(alm.year,alm.month,alm.day);
	double d = t - 2415020;
	RDUMP(d);
	float S0 = 0.276919398 + 0.00273790926493*d+0.1075231*pow(10.0,-5.0)*(d/36525.0);
	RDUMP(S0);
	
	double tStar = t - alm.Tlambda + 86400.0*(N0-Na);
	RDUMP(tStar);
	double Wk = tStar/Tdr;
	RDUMP(Wk);
	int W   = (int) Wk;
	RDUMP(W);
	double tlk = alm.Tlambda + Tdr * W + alm.dTT * pow(W,2.0);
	RDUMP(tlk);
	tlk = (int) tlk%86400; // mod
	RDUMP(tlk);
	// =====================
	
	double n = (2.0*PI)/Tdr;
	
	double omBigHatch = (3.0/2.0)*alm.C*n*pow((alm.ae/a),2.0)*cos(i)*pow((1.0-pow(alm.e,2.0)),-2.0);
	
	double lk = alm.lambda + (omBigHatch - alm.omEarth)*(Tdr*W+alm.dTT*pow(W,2.0));
	
	double S = S0 + alm.omEarth*(tlk-10800);
	
	double omBig = lk + S;
	
	
	// 3. Вычисление констант интегрирования
	
	double J = (-3.0/2.0)*alm.C;
	double l = alm.e*cos(alm.w);
	double h = alm.e*sin(alm.w);

	double E = 2.0*atan(sqrt((1.0-alm.e)/(1.0+alm.e))*tan(v/2.0));
	double M = E - alm.e*sin(E);
	
	double lambdaHatch = M + alm.w;
	
	// ======================================================
	double m = 1;
	double ro = 0;
	
	double da_1 = (2*J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*(alm.lambda*cos(lambdaHatch)+h*sin(lambdaHatch))+J*pow((alm.ae/a),2)*pow(sin(i),2)*(0.5*h*sin(lambdaHatch)-0.5*l*cos(lambdaHatch)+cos(2*lambdaHatch)+(7/2)*l*cos(3*lambdaHatch)+(7/2)*h*sin(3*lambdaHatch)))/a;
	
	double dh_1 = J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*( l*n*ro+sin(lambdaHatch)+(3/2)*l*sin(2*lambdaHatch)-(3/2)*h*cos(2*lambdaHatch)) - (1/4)*J*pow((alm.ae/a),2)*pow(sin(i),2)*( sin(lambdaHatch)-(7/3)*sin(3*lambdaHatch)+5*l*sin(2*lambdaHatch)-(17/2)*l*sin(4*lambdaHatch)+(17/2)*h*cos(4*lambdaHatch)+h*cos(2*lambdaHatch))+J*pow((alm.ae/a),2)*pow(cos(i),2)*( l*n*ro-(1/2)*l*sin(2*lambdaHatch));
	
	double dl_1 = J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*(-h*n*ro+cos(lambdaHatch)+(3/2)*l*cos(2*lambdaHatch)+(3/2)*h*sin(2*lambdaHatch)) - (1/4)*J*pow((alm.ae/a),2)*pow(sin(i),2)*(-cos(lambdaHatch)-(7/3)*sin(3*lambdaHatch)-5*h*sin(2*lambdaHatch)-(17/2)*l*cos(4*lambdaHatch)-(17/2)*h*sin(4*lambdaHatch)+l*cos(2*lambdaHatch))+J*pow((alm.ae/a),2)*pow(cos(i),2)*(-h*n*ro+(1/2)*h*sin(2*lambdaHatch));
	
	double domBig_1 = -J*pow((alm.ae/a),2)*cos(i)*(n*ro+(7/2)*l*sin(lambdaHatch)-(5/2)*h*cos(lambdaHatch)-(1/2)*sin(2*lambdaHatch)-(7/6)*l*sin(3*lambdaHatch)+(7/6)*h*cos(3*lambdaHatch));
	
	double di_1 = (1/2)*J*pow((alm.ae/a),2)*sin(i)*cos(i)*(-l*cos(lambdaHatch)+h*sin(lambdaHatch)+cos(2*lambdaHatch)+(7/3)*l*cos(3*lambdaHatch)+(7/3)*h*sin(3*lambdaHatch));
	
	double dlambda_1 = 2*J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*(n*ro+(7/4)*l*sin(lambdaHatch)-(7/4)*h*cos(2*lambdaHatch))+3*J*pow((alm.ae/a),2)*pow((sin(i)),2)*((-7/24)*h*cos(lambdaHatch)-(7/24)*l*sin(lambdaHatch)-(49/72)*l*sin(3*lambdaHatch)+(1/4)*sin(2*lambdaHatch))+J*pow((alm.ae/a),2)*pow(cos(i),2)*(n*ro+(7/2)*l*sin(lambdaHatch)-(5/2)*h*cos(lambdaHatch)-(1/2)*sin(2*lambdaHatch)-(7/6)*l*sin(3*lambdaHatch)+(7/6)*h*cos(3*lambdaHatch));
	
	// ======================================================
	m = 2;
	ro = t - tlk;
	lambdaHatch = M + alm.w + n*ro;
	
	double da_2 = (2*J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*(alm.lambda*cos(lambdaHatch)+h*sin(lambdaHatch))+J*pow((alm.ae/a),2)*pow(sin(i),2)*(0.5*h*sin(lambdaHatch)-0.5*l*cos(lambdaHatch)+cos(2*lambdaHatch)+(7/2)*l*cos(3*lambdaHatch)+(7/2)*h*sin(3*lambdaHatch)))/a;
	
	double dh_2 = J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*( l*n*ro+sin(lambdaHatch)+(3/2)*l*sin(2*lambdaHatch)-(3/2)*h*cos(2*lambdaHatch)) - (1/4)*J*pow((alm.ae/a),2)*pow(sin(i),2)*( sin(lambdaHatch)-(7/3)*sin(3*lambdaHatch)+5*l*sin(2*lambdaHatch)-(17/2)*l*sin(4*lambdaHatch)+(17/2)*h*cos(4*lambdaHatch)+h*cos(2*lambdaHatch))+J*pow((alm.ae/a),2)*pow(cos(i),2)*( l*n*ro-(1/2)*l*sin(2*lambdaHatch));
	
	double dl_2 = J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*(-h*n*ro+cos(lambdaHatch)+(3/2)*l*cos(2*lambdaHatch)+(3/2)*h*sin(2*lambdaHatch)) - (1/4)*J*pow((alm.ae/a),2)*pow(sin(i),2)*(-cos(lambdaHatch)-(7/3)*sin(3*lambdaHatch)-5*h*sin(2*lambdaHatch)-(17/2)*l*cos(4*lambdaHatch)-(17/2)*h*sin(4*lambdaHatch)+l*cos(2*lambdaHatch))+J*pow((alm.ae/a),2)*pow(cos(i),2)*(-h*n*ro+(1/2)*h*sin(2*lambdaHatch));
	
	double domBig_2 = -J*pow((alm.ae/a),2)*cos(i)*(n*ro+(7/2)*l*sin(lambdaHatch)-(5/2)*h*cos(lambdaHatch)-(1/2)*sin(2*lambdaHatch)-(7/6)*l*sin(3*lambdaHatch)+(7/6)*h*cos(3*lambdaHatch));
	
	double di_2 = (1/2)*J*pow((alm.ae/a),2)*sin(i)*cos(i)*(-l*cos(lambdaHatch)+h*sin(lambdaHatch)+cos(2*lambdaHatch)+(7/3)*l*cos(3*lambdaHatch)+(7/3)*h*sin(3*lambdaHatch));
	
	double dlambda_2 = 2*J*pow((alm.ae/a),2)*(1-(3/2)*pow((sin(i)),2))*(n*ro+(7/4)*l*sin(lambdaHatch)-(7/4)*h*cos(2*lambdaHatch))+3*J*pow((alm.ae/a),2)*pow((sin(i)),2)*((-7/24)*h*cos(lambdaHatch)-(7/24)*l*sin(lambdaHatch)-(49/72)*l*sin(3*lambdaHatch)+(1/4)*sin(2*lambdaHatch))+J*pow((alm.ae/a),2)*pow(cos(i),2)*(n*ro+(7/2)*l*sin(lambdaHatch)-(5/2)*h*cos(lambdaHatch)-(1/2)*sin(2*lambdaHatch)-(7/6)*l*sin(3*lambdaHatch)+(7/6)*h*cos(3*lambdaHatch));
	
	
	//4. Вычисление поправок к элементам орбиты НКА
	
	double da      = da_2 - da_1;
	double dh      = dh_2 - dh_1;
	double dl      = dl_2 - dl_1;
	double domBig  = domBig_2 - domBig_1;
	double di      = di_2 - di_1;
	double dlambda = dlambda_2 - dlambda_1;

	//5. Вычисление возмущенных элементов орбиты НКА
	
	h = h + dh;
	l = l + dl;
	
	double eps = sqrt(sqr(h)+sqr(l));
	double omMIN;
	
	if ((eps != 0) && (eps != 0))
		omMIN = atan(h/l);
	else if (eps == 0)
			omMIN = 0;
		else if ((eps != 0) && (h == eps))
				omMIN = PI/2;
			else if ((eps != 0) && (h == -eps))
				omMIN = -PI/2;
			
	a = a + da;
	i = i + di;
	omBig = omBig + domBig;
	double lStar = M + alm.w + n*(t-tlk)+dlambda;
	M = lStar - omMIN;
	
	//6. Вычисление координат
	CKeplerian kepTest;
	
	kepTest.M = M;
	kepTest.e = eps;
	
	kepTest.exAnomCalc();

	E = kepTest.E;
	
	v = 2*atan(sqrt((1-eps)/(1+eps))*tan(E/2.0));
		
	double u = v + alm.w;
	
	double r = a*(1-eps*cos(E));
	
	car.x = r*(cos(u)*cos(omBig) - sin(u)*sin(omBig)*cos(i));
	car.y = r*(cos(u)*sin(omBig) + sin(u)*cos(omBig)*cos(i));
	car.z = r*(sin(u)*sin(i));
	
	RDUMP(car.x);
	RDUMP(car.y);
	RDUMP(car.z);
	return car;
}
