#include<cstdio>
char s[30][30][30]={{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","10","","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","102","102","","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","1020","1020","1020","","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","10200","10200","10200","10000","","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","102000","102000","102000","100002","100002","","","","","","","","","","","","","","","","","","","","","","","",""},
{"","1020005","1020005","1020005","1000020","1000020","1000020","","","","","","","","","","","","","","","","","","","","","","",""},
{"","10200056","10200056","10200056","10000200","10000200","10000200","10000064","","","","","","","","","","","","","","","","","","","","","",""},
{"","102000564","102000564","102000564","100002006","100002006","100002006","100000647","100000008","","","","","","","","","","","","","","","","","","","","",""},
{"","1020005640","1020005640","1020005640","1000020060","1000020060","1000020060","1000006470","1000000080","1000000080","","","","","","","","","","","","","","","","","","","",""},
{"","10200056405","10200056405","10200056405","10000200606","10000200606","10000200606","10000064701","10000000802","10000000802","10000000109","","","","","","","","","","","","","","","","","","",""},
{"","102006162060","102006162060","102006162060","100002006060","100002006060","100002006060","100000647012","100000008024","100000008024","100000002084","100000000104","","","","","","","","","","","","","","","","","",""},
{"","1020061620604","1020061620604","1020061620604","1000027260128","1000027260128","1000027260128","1000006470125","1000000080248","1000000080248","1000000060449","1000000005485","1000000000207","","","","","","","","","","","","","","","","",""},
{"","10200616206046","10200616206046","10200616206046","10000272601284","10000272601284","10000272601284","10000064701256","10000000802484","10000000802484","10000000604496","10000000054856","10000000002076","10000000000256","","","","","","","","","","","","","","","",""},
{"","102006162060465","102006162060465","102006162060465","100002726012840","100002726012840","100002726012840","100001367072180","100000008024840","100000008024840","100000006044960","100000000764300","100000000020765","100000000006485","100000000000185","","","","","","","","","","","","","","",""},
{"","1020061620604656","1020061620604656","1020061620604656","1000027260128400","1000027260128400","1000027260128400","1000013670721808","1000000080248400","1000000080248400","1000000060449600","1000000007643008","1000000000805408","1000000000077456","1000000000001856","1000000000000208","","","","","","","","","","","","","",""},
{"","10200616206046568","10200616206046568","10200616206046568","10000832402470569","10000832402470569","10000832402470569","10000136707218087","10000072808446565","10000001704812002","10000001209254080","10000000087224007","10000000008054089","10000000001166080","10000000000018563","10000000000006561","10000000000000169","","","","","","","","","","","","",""},
{"","108054801036000018","108054801036000018","108054801036000018","101208807048720006","100956888012540816","100116162084960054","100003446072465678","100001763072960030","100000179072360072","100000012092540804","100000004832000090","100000000200105630","100000000011660804","100000000000740852","100000000000065618","100000000000006452","100000000000000332","","","","","","","","","","","",""},
{"","1080548010360000180","1080548010360000180","1080548010360000180","1016582400964208520","1016582400964208520","1001406420365408286","1000034460724656782","1000017630729600301","1000001880969008586","1000000130883600069","1000000073644656126","1000000002001056306","1000000000480656242","1000000000015808227","1000000000000656183","1000000000000064523","1000000000000003324","1000000000000000265","","","","","","","","","","",""},
{"","10805480103600001800","10805480103600001800","10805480103600001800","10165824009642085200","10165824009642085200","10014064203654082860","10000344607246567820","10000344607246567820","10000018809690085860","10000011901236001220","10000000736446561260","10000000020010563060","10000000004806562420","10000000000438565400","10000000000027522820","10000000000003042840","10000000000000033240","10000000000000006260","10000000000000000180","","","","","","","","","",""},
{"","123606009012225672009","123606009012225672009","123606009012225672009","104052249072240066402","104052249072240066402","101082888060705684000","100003446072465678204","100003446072465678204","100000188096900858606","100000119012360012201","100000007364465612600","100000002384105660606","100000000120860810600","100000000009140894201","100000000000635282009","100000000000033650804","100000000000001016405","100000000000000062606","100000000000000039800","100000000000000000005","","","","","","","","",""},
{"","1236060090122256720090","1236060090122256720090","1236060090122256720090","1040522490722400664022","1040522490722400664022","1029126420361200420006","1000034460724656782040","1000034460724656782040","1000001880969008586064","1000001190123600122018","1000000122004800908046","1000000023841056606060","1000000003548000244020","1000000000091408942010","1000000000006352820090","1000000000001744104022","1000000000000010164056","1000000000000000626066","1000000000000000474024","1000000000000000000056","1000000000000000000056","","","","","","","",""},
{"","12360600901222567200901","12360600901222567200901","12360600901222567200901","10405224907224006640223","10405224907224006640223","10326688207290084640567","10022184007290082800925","10003824006022562480160","10001501103622563080700","10000084204894563040805","10000001220048009080461","10000000881654084060982","10000000035480002440203","10000000001964009660049","10000000000939521680145","10000000000021606220147","10000000000000101640564","10000000000000006260668","10000000000000005880501","10000000000000000120243","10000000000000000008923","10000000000000000000344","","","","","","",""},
{"","144408645048225636603816","144408645048225636603816","144408645048225636603816","144408645048225636603816","119952000084840030408408","103266882072900846405672","100706967024300864801288","100038240060225624801600","100015011036225630807000","100004993004840012201288","100000146732225624801456","100000019772945648006240","100000000579785678204888","100000000038825612600600","100000000009395216801456","100000000000441656801480","100000000000001016405648","100000000000001016405648","100000000000000123401432","100000000000000001202432","100000000000000000131096","100000000000000000003440","100000000000000000000224","","","","","",""},
{"","3608528850368400786036725","3608528850368400786036725","3608528850368400786036725","1828022400607200846092400","1301587290367056900064800","1032668820729008464056725","1012788810007808586060725","1000382400602256248016000","1000150110362256308070000","1000080030482400064054325","1000004058963008284086000","1000000197729456480062400","1000000050595056546002400","1000000000388256126006000","1000000000116752586006725","1000000000004416568014800","1000000000004416568014800","1000000000000019702046000","1000000000000001234014325","1000000000000000012024325","1000000000000000010550000","1000000000000000000034400","1000000000000000000006800","1000000000000000000000325","","","","",""},
{"","-1","-1","75320424003636007240884008","18280224006072008460924002","13015872903670569000648008","10326688207290084640567258","10326688207290084640567258","10003824006022562480160006","10003824006022562480160006","10000800304824000640543250","10000155957610563000967256","10000007881248007860384004","10000001600946082840848006","10000000106166087000943258","10000000001167525860067258","10000000000044165680148008","10000000000044165680148008","10000000000001107880743258","10000000000000036280107256","10000000000000000120243256","10000000000000000105500008","10000000000000000001448008","10000000000000000000068006","10000000000000000000015252","10000000000000000000000250","","","",""},
{"","-1","-1","753204240036360072408840084","753204240036360072408840084","528552567072465642000840006","392088960012120066801672588","140865282036780876603600003","100038240060225624801600066","100038240060225624801600066","100019420052585642609000003","100001559576105630009672561","100000093788420804006672546","100000038191340816606000042","100000001748780810600072507","100000000061160048003000087","100000000000441656801480087","100000000000441656801480087","100000000000023444006480081","100000000000001164602000024","100000000000000001202432561","100000000000000001055000087","100000000000000000014480081","100000000000000000004592546","100000000000000000000392507","100000000000000000000017585","100000000000000000000000683","","",""},
{"","-1","-1","7532042400363600724088400840","7532042400363600724088400840","7532042400363600724088400840","3920889600121200668016725880","1408652820367808766036000036","1015500060367808224022400608","1001385810724656966004325888","1001159170089456786034325496","1000023746761200244028400000","1000000937884208040066725460","1000000381913408166060000420","1000000029931056724086725040","1000000004165856722072400216","1000000000484656388074325076","1000000000011882960090000000","1000000000000273504056000848","1000000000000013964006000428","1000000000000002242010000420","1000000000000000047092400272","1000000000000000006062725880","1000000000000000000045925468","1000000000000000000003925076","1000000000000000000000225268","1000000000000000000000022492","1000000000000000000000000624","",""},
{"","-1","-1","-1","-1","-1","39208896001212006680167258804","18555536703606084000060008482","10211576408418088880443254681","10101279606082569080443254680","10015192000842085860660000924","10000351372830084060967250126","10000028419290081060024006085","10000003819134081660600004206","10000000299310567240867250403","10000000177423525880167258806","10000000012965287440500008129","10000000000552924880760008767","10000000000010730620467258241","10000000000000635540300008128","10000000000000024060207252565","10000000000000000485667250123","10000000000000000135423252801","10000000000000000007244006366","10000000000000000001503258209","10000000000000000000006750880","10000000000000000000000224923","10000000000000000000000141200","10000000000000000000000000086",""}};
main()
{
    int n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        printf("Case %d: %s\n",C++,s[m][n]);
    }
}
