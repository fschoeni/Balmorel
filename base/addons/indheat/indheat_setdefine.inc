SET
INDHEAT_GROUP 'Group of technologies' %semislash%
$if     EXIST '../data/INDHEAT_GROUP.inc' $INCLUDE         '../data/INDHEAT_GROUP.inc';
$if not EXIST '../data/INDHEAT_GROUP.inc' $INCLUDE '../../base/data/INDHEAT_GROUP.inc';
%semislash%

SET
INDHEAT_SUMGROUP 'Summed group of technologies' %semislash%
$if     EXIST '../data/INDHEAT_SUMGROUP.inc' $INCLUDE         '../data/INDHEAT_SUMGROUP.inc';
$if not EXIST '../data/INDHEAT_SUMGROUP.inc' $INCLUDE '../../base/data/INDHEAT_SUMGROUP.inc';
%semislash%

SET
INDHEAT_RELGROUP(INDHEAT_SUMGROUP,INDHEAT_GROUP) 'Relation of summed groups and groups' %semislash%
$if     EXIST '../data/INDHEAT_RELGROUP.inc' $INCLUDE         '../data/INDHEAT_RELGROUP.inc';
$if not EXIST '../data/INDHEAT_RELGROUP.inc' $INCLUDE '../../base/data/INDHEAT_RELGROUP.inc';
%semislash%

$onmulti
$if     EXIST '../data/INDHEAT_CCCRRRAAA.inc' $INCLUDE         '../data/INDHEAT_CCCRRRAAA.inc';
$if not EXIST '../data/INDHEAT_CCCRRRAAA.inc' $INCLUDE '../../base/data/INDHEAT_CCCRRRAAA.inc';
$offmulti

SET
INDHEAT_AAA(AAA) 'Areas with individual heating' %semislash%
$if     EXIST '../data/INDHEAT_AAA.inc' $INCLUDE         '../data/INDHEAT_AAA.inc';
$if not EXIST '../data/INDHEAT_AAA.inc' $INCLUDE '../../base/data/INDHEAT_AAA.inc';
%semislash%

$onmulti
$if     EXIST '../data/INDHEAT_RRRAAA.inc' $INCLUDE         '../data/INDHEAT_RRRAAA.inc';
$if not EXIST '../data/INDHEAT_RRRAAA.inc' $INCLUDE '../../base/data/INDHEAT_RRRAAA.inc';
$offmulti

SET
INDHEAT_GGG 'Individual heating technologies' %semislash%
$if     EXIST '../data/INDHEAT_GGG.inc' $INCLUDE         '../data/INDHEAT_GGG.inc';
$if not EXIST '../data/INDHEAT_GGG.inc' $INCLUDE '../../base/data/INDHEAT_GGG.inc';
%semislash%

SET
INDHEAT_DHUSER 'Individual heating user groups' %semislash%
$if     EXIST '../data/INDHEAT_DHUSER.inc' $INCLUDE         '../data/INDHEAT_DHUSER.inc';
$if not EXIST '../data/INDHEAT_DHUSER.inc' $INCLUDE '../../base/data/INDHEAT_DHUSER.inc';
%semislash%

SET
INDHEAT_G(INDHEAT_GGG) 'Individual heating technologies in simulation' %semislash%
$if     EXIST '../data/INDHEAT_G.inc' $INCLUDE         '../data/INDHEAT_G.inc';
$if not EXIST '../data/INDHEAT_G.inc' $INCLUDE '../../base/data/INDHEAT_G.inc';
%semislash%

SET
INDHEAT_GTODHUSER(INDHEAT_GGG,INDHEAT_DHUSER) 'Individual heating technologies combined with user group'%semislash%
$if     EXIST '../data/INDHEAT_GTODHUSER.inc' $INCLUDE         '../data/INDHEAT_GTODHUSER.inc';
$if not EXIST '../data/INDHEAT_GTODHUSER.inc' $INCLUDE '../../base/data/INDHEAT_GTODHUSER.inc';
%semislash%

SET
INDHEAT_GINGROUP(INDHEAT_GGG,INDHEAT_GROUP) 'Technologies belonging to each group' %semislash%
$if     EXIST '../data/INDHEAT_GINGROUP.inc' $INCLUDE         '../data/INDHEAT_GINGROUP.inc';
$if not EXIST '../data/INDHEAT_GINGROUP.inc' $INCLUDE '../../base/data/INDHEAT_GINGROUP.inc';
%semislash%

ALIAS(INDHEAT_GROUP, INDHEAT_GROUPFROM);
ALIAS(INDHEAT_GROUP, INDHEAT_GROUPTO);
ALIAS(INDHEAT_GGG,INDHEAT_IGGGALIAS);
ALIAS(INDHEAT_G,INDHEAT_GALIAS);
ALIAS(INDHEAT_G,INDHEAT_GALIAS2);

SET
INDHEAT_GMOVE(INDHEAT_GGG,INDHEAT_GROUPFROM,INDHEAT_GROUPTO) 'Technologies that can be moved from group GROUPFROM to GROUPTO' %semislash%
$if     EXIST '../data/INDHEAT_GMOVE.inc' $INCLUDE         '../data/INDHEAT_GMOVE.inc';
$if not EXIST '../data/INDHEAT_GMOVE.inc' $INCLUDE '../../base/data/INDHEAT_GMOVE.inc';
%semislash%

$ifi not %COMBTECH%==yes $goto endcombtech
SET
INDHEAT_GGCOMB(INDHEAT_GGG,INDHEAT_IGGGALIAS) 'Combination technologies' %semislash%
$if     EXIST '../data/INDHEAT_GGCOMB.inc' $INCLUDE         '../data/INDHEAT_GGCOMB.inc';
$if not EXIST '../data/INDHEAT_GGCOMB.inc' $INCLUDE '../../base/data/INDHEAT_GGCOMB.inc';
%semislash%
$label endcombtech