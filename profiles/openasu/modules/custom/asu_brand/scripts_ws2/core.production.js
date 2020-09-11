!function(n,e){"object"==typeof exports&&"object"==typeof module?module.exports=e():"function"==typeof define&&define.amd?define("AsuWebcore",[],e):"object"==typeof exports?exports.AsuWebcore=e():n.AsuWebcore=e()}(window,(function(){return function(n){function e(e){for(var o,a,d=e[0],u=e[1],c=e[2],l=0,f=[];l<d.length;l++)a=d[l],Object.prototype.hasOwnProperty.call(r,a)&&r[a]&&f.push(r[a][0]),r[a]=0;for(o in u)Object.prototype.hasOwnProperty.call(u,o)&&(n[o]=u[o]);for(s&&s(e);f.length;)f.shift()();return i.push.apply(i,c||[]),t()}function t(){for(var n,e=0;e<i.length;e++){for(var t=i[e],o=!0,d=1;d<t.length;d++){var u=t[d];0!==r[u]&&(o=!1)}o&&(i.splice(e--,1),n=a(a.s=t[0]))}return n}var o={},r={0:0},i=[];function a(e){if(o[e])return o[e].exports;var t=o[e]={i:e,l:!1,exports:{}};return n[e].call(t.exports,t,t.exports,a),t.l=!0,t.exports}a.m=n,a.c=o,a.d=function(n,e,t){a.o(n,e)||Object.defineProperty(n,e,{enumerable:!0,get:t})},a.r=function(n){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(n,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(n,"__esModule",{value:!0})},a.t=function(n,e){if(1&e&&(n=a(n)),8&e)return n;if(4&e&&"object"==typeof n&&n&&n.__esModule)return n;var t=Object.create(null);if(a.r(t),Object.defineProperty(t,"default",{enumerable:!0,value:n}),2&e&&"string"!=typeof n)for(var o in n)a.d(t,o,function(e){return n[e]}.bind(null,o));return t},a.n=function(n){var e=n&&n.__esModule?function(){return n.default}:function(){return n};return a.d(e,"a",e),e},a.o=function(n,e){return Object.prototype.hasOwnProperty.call(n,e)},a.p="";var d=window.webpackJsonpAsuWeb_name_=window.webpackJsonpAsuWeb_name_||[],u=d.push.bind(d);d.push=e,d=d.slice();for(var c=0;c<d.length;c++)e(d[c]);var s=u;return i.push([13,1]),t()}({13:function(n,e,t){"use strict";t.r(e),t.d(e,"Button",(function(){return Ya})),t.d(e,"FoldableCard",(function(){return pd})),t.d(e,"Header",(function(){return mu})),t.d(e,"Heading",(function(){return _d})),t.d(e,"Icon",(function(){return ud})),t.d(e,"Nav",(function(){return nu})),t.d(e,"Panel",(function(){return gu})),t.d(e,"HydratePreact",(function(){return i})),t.d(e,"RenderPreact",(function(){return a})),t.d(e,"initHeader",(function(){return d}));var o={};t.r(o),t.d(o,"AssetFontIconName",(function(){return f})),t.d(o,"AssetFontIconTtf",(function(){return m})),t.d(o,"AssetFontIconEot",(function(){return p})),t.d(o,"AssetFontIconWoff",(function(){return g})),t.d(o,"AssetFontIconWoff2",(function(){return h})),t.d(o,"AssetFontIconSvg",(function(){return b})),t.d(o,"BreakpointXs",(function(){return C})),t.d(o,"BreakpointSm",(function(){return B})),t.d(o,"BreakpointMd",(function(){return y})),t.d(o,"BreakpointLg",(function(){return O})),t.d(o,"BreakpointXl",(function(){return x})),t.d(o,"BreakpointXxl",(function(){return S})),t.d(o,"BreakpointXxxl",(function(){return v})),t.d(o,"ColorAlertsError",(function(){return w})),t.d(o,"ColorAlertsWarning",(function(){return L})),t.d(o,"ColorAlertsInfo",(function(){return H})),t.d(o,"ColorAlertsSuccess",(function(){return j})),t.d(o,"ColorBackgroundWhite",(function(){return k})),t.d(o,"ColorBackgroundGray",(function(){return P})),t.d(o,"ColorBackgroundDark",(function(){return F})),t.d(o,"ColorBackgroundSuccess",(function(){return z})),t.d(o,"ColorBackgroundError",(function(){return T})),t.d(o,"ColorBackgroundWarning",(function(){return M})),t.d(o,"ColorBackgroundInfo",(function(){return $})),t.d(o,"ColorBackgroundOverlay",(function(){return D})),t.d(o,"ColorBaseGold",(function(){return I})),t.d(o,"ColorBaseMaroon",(function(){return U})),t.d(o,"ColorBaseWhite",(function(){return W})),t.d(o,"ColorBaseGreen",(function(){return A})),t.d(o,"ColorBaseOrange",(function(){return R})),t.d(o,"ColorBaseBlue",(function(){return G})),t.d(o,"ColorBaseBluefocus",(function(){return X})),t.d(o,"ColorBaseDarkgold",(function(){return N})),t.d(o,"ColorBaseDarkmaroon",(function(){return E})),t.d(o,"ColorBaseGray1",(function(){return Y})),t.d(o,"ColorBaseGray2",(function(){return _})),t.d(o,"ColorBaseGray3",(function(){return q})),t.d(o,"ColorBaseGray4",(function(){return V})),t.d(o,"ColorBaseGray5",(function(){return K})),t.d(o,"ColorBaseGray6",(function(){return J})),t.d(o,"ColorBaseGray7",(function(){return Q})),t.d(o,"ColorBorderLight",(function(){return Z})),t.d(o,"ColorBorderBase",(function(){return nn})),t.d(o,"ColorBorderDark",(function(){return en})),t.d(o,"ColorBorderFocus",(function(){return tn})),t.d(o,"ColorBorderError",(function(){return on})),t.d(o,"ColorBorderWarning",(function(){return rn})),t.d(o,"ColorBorderSuccess",(function(){return an})),t.d(o,"ColorBorderInfo",(function(){return dn})),t.d(o,"ColorBrandGold",(function(){return un})),t.d(o,"ColorBrandMaroon",(function(){return cn})),t.d(o,"ColorBrandDark",(function(){return sn})),t.d(o,"ColorBrandLight",(function(){return ln})),t.d(o,"ColorFontDarkBase",(function(){return fn})),t.d(o,"ColorFontDarkLink",(function(){return mn})),t.d(o,"ColorFontDarkHover",(function(){return pn})),t.d(o,"ColorFontDarkActive",(function(){return gn})),t.d(o,"ColorFontDarkVisited",(function(){return hn})),t.d(o,"ColorFontDarkError",(function(){return bn})),t.d(o,"ColorFontDarkWarning",(function(){return Cn})),t.d(o,"ColorFontDarkSuccess",(function(){return Bn})),t.d(o,"ColorFontDarkInfo",(function(){return yn})),t.d(o,"ColorFontLightBase",(function(){return On})),t.d(o,"ColorFontLightLink",(function(){return xn})),t.d(o,"ColorFontLightHover",(function(){return Sn})),t.d(o,"ColorFontLightActive",(function(){return vn})),t.d(o,"ColorFontLightVisited",(function(){return wn})),t.d(o,"ColorFontLightError",(function(){return Ln})),t.d(o,"ColorFontLightWarning",(function(){return Hn})),t.d(o,"ColorFontLightSuccess",(function(){return jn})),t.d(o,"ColorFontLightInfo",(function(){return kn})),t.d(o,"ColorDividerDarker",(function(){return Pn})),t.d(o,"ColorDividerLighter",(function(){return Fn})),t.d(o,"FontFamilyBase",(function(){return zn})),t.d(o,"FontFamilyIcons",(function(){return Tn})),t.d(o,"FontWeightLighter",(function(){return Mn})),t.d(o,"FontWeightLight",(function(){return $n})),t.d(o,"FontWeightNormal",(function(){return Dn})),t.d(o,"FontWeightBold",(function(){return In})),t.d(o,"FontWeightBolder",(function(){return Un})),t.d(o,"FontWeightBase",(function(){return Wn})),t.d(o,"GridContainerMaxWidthSm",(function(){return An})),t.d(o,"GridContainerMaxWidthMd",(function(){return Rn})),t.d(o,"GridContainerMaxWidthLg",(function(){return Gn})),t.d(o,"GridContainerMaxWidthXl",(function(){return Xn})),t.d(o,"GridColumnCount",(function(){return Nn})),t.d(o,"GridGutterWidth",(function(){return En})),t.d(o,"SizeBreakpointsSmall",(function(){return Yn})),t.d(o,"SizeBreakpointsMedium",(function(){return _n})),t.d(o,"SizeBreakpointsLarge",(function(){return qn})),t.d(o,"SizeFontTiny",(function(){return Vn})),t.d(o,"SizeFontSmall",(function(){return Kn})),t.d(o,"SizeFontMedium",(function(){return Jn})),t.d(o,"SizeFontLarge",(function(){return Qn})),t.d(o,"SizeFontXl",(function(){return Zn})),t.d(o,"SizeFontXxl",(function(){return ne})),t.d(o,"SizeFontXxxl",(function(){return ee})),t.d(o,"SizeFontBase",(function(){return te})),t.d(o,"SizeIconSmall",(function(){return oe})),t.d(o,"SizeIconBase",(function(){return re})),t.d(o,"SizeIconLarge",(function(){return ie})),t.d(o,"SizeIconXl",(function(){return ae})),t.d(o,"SizeIconXxl",(function(){return de})),t.d(o,"SizeSpacing0",(function(){return ue})),t.d(o,"SizeSpacing1",(function(){return ce})),t.d(o,"SizeSpacing2",(function(){return se})),t.d(o,"SizeSpacing3",(function(){return le})),t.d(o,"SizeSpacing4",(function(){return fe})),t.d(o,"SizeSpacing5",(function(){return me})),t.d(o,"SizeSpacing6",(function(){return pe})),t.d(o,"SizeSpacing7",(function(){return ge})),t.d(o,"SizeSpacing8",(function(){return he})),t.d(o,"SizeSpacing9",(function(){return be})),t.d(o,"SizeSpacing10",(function(){return Ce})),t.d(o,"SizeSpacing12",(function(){return Be})),t.d(o,"SizeSpacing14",(function(){return ye})),t.d(o,"SizeSpacing16",(function(){return Oe})),t.d(o,"SizeSpacing32",(function(){return xe})),t.d(o,"SizeSpacing64",(function(){return Se})),t.d(o,"SizeSpacingHalf",(function(){return ve})),t.d(o,"SizeSpacingBase",(function(){return we})),t.d(o,"WeightFontRegular",(function(){return Le})),t.d(o,"WeightFontBold",(function(){return He})),t.d(o,"TimeTransitionShort",(function(){return je})),t.d(o,"TimeTransitionBase",(function(){return ke})),t.d(o,"TimeTransitionLong",(function(){return Pe})),t.d(o,"TimeTransitionXl",(function(){return Fe})),t.d(o,"TimeDelayShort",(function(){return ze})),t.d(o,"TimeDelayBase",(function(){return Te})),t.d(o,"TimeDelayLong",(function(){return Me})),t.d(o,"TimeDurationShort",(function(){return $e})),t.d(o,"TimeDurationBase",(function(){return De})),t.d(o,"TimeDurationLong",(function(){return Ie})),t.d(o,"ComponentBreadcrumbFontSize",(function(){return Ue})),t.d(o,"ComponentBreadcrumbPaddingY",(function(){return We})),t.d(o,"ComponentBreadcrumbPaddingX",(function(){return Ae})),t.d(o,"ComponentBreadcrumbItemPadding",(function(){return Re})),t.d(o,"ComponentBreadcrumbMarginBottom",(function(){return Ge})),t.d(o,"ComponentBreadcrumbBg",(function(){return Xe})),t.d(o,"ComponentBreadcrumbDividerColor",(function(){return Ne})),t.d(o,"ComponentBreadcrumbActiveColor",(function(){return Ee})),t.d(o,"ComponentBreadcrumbDivider",(function(){return Ye})),t.d(o,"ComponentBreadcrumbBorderRadiusNone",(function(){return _e})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemPaddingLeftPx",(function(){return qe})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemFirstOfTypePaddingLeft",(function(){return Ve})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemPlusBreadcrumbItemBeforePaddingLeft",(function(){return Ke})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemPlusBreadcrumbItemBeforePaddingRight",(function(){return Je})),t.d(o,"ComponentButtonBackgroundOrigin",(function(){return Qe})),t.d(o,"ComponentButtonBackgroundPosition",(function(){return Ze})),t.d(o,"ComponentButtonBackgroundRepeat",(function(){return nt})),t.d(o,"ComponentButtonBorderRadius",(function(){return et})),t.d(o,"ComponentButtonDisplay",(function(){return tt})),t.d(o,"ComponentButtonFontWeight",(function(){return ot})),t.d(o,"ComponentButtonTextDecoration",(function(){return rt})),t.d(o,"ComponentButtonLineHeight",(function(){return it})),t.d(o,"ComponentButtonMaxWidth",(function(){return at})),t.d(o,"ComponentButtonHoverStateTransform",(function(){return dt})),t.d(o,"ComponentButtonActiveStateTransform",(function(){return ut})),t.d(o,"ComponentButtonPadding",(function(){return ct})),t.d(o,"ComponentButtonPaddingY",(function(){return st})),t.d(o,"ComponentButtonPaddingX",(function(){return lt})),t.d(o,"ComponentButtonPaddingYMedium",(function(){return ft})),t.d(o,"ComponentButtonPaddingXMedium",(function(){return mt})),t.d(o,"ComponentButtonPaddingXSmall",(function(){return pt})),t.d(o,"ComponentButtonPaddingYSmall",(function(){return gt})),t.d(o,"ComponentButtonTextAlign",(function(){return ht})),t.d(o,"ComponentButtonTransition",(function(){return bt})),t.d(o,"ComponentButtonDisabledOpacity",(function(){return Ct})),t.d(o,"ComponentButtonBadgeBackgroundColor",(function(){return Bt})),t.d(o,"ComponentButtonBadgeBorderRadius",(function(){return yt})),t.d(o,"ComponentButtonBadgeFontWeight",(function(){return Ot})),t.d(o,"ComponentButtonBadgeHeight",(function(){return xt})),t.d(o,"ComponentButtonCloseHeight",(function(){return St})),t.d(o,"ComponentButtonCloseOpacity",(function(){return vt})),t.d(o,"ComponentButtonCloseWidth",(function(){return wt})),t.d(o,"ComponentButtonCloseDisabledOpacity",(function(){return Lt})),t.d(o,"ComponentButtonCloseWhiteBackgroundColor",(function(){return Ht})),t.d(o,"ComponentButtonCloseGrayBackgroundColor",(function(){return jt})),t.d(o,"ComponentButtonCarouselPositionHeight",(function(){return kt})),t.d(o,"ComponentButtonCarouselPositionWidth",(function(){return Pt})),t.d(o,"ComponentButtonCarouselPositionInactiveBackgroundColor",(function(){return Ft})),t.d(o,"ComponentButtonCarouselPositionInactiveOpacity",(function(){return zt})),t.d(o,"ComponentButtonCarouselPositionBlackBackgroundColor",(function(){return Tt})),t.d(o,"ComponentButtonCarouselPositionWhiteBackgroundColor",(function(){return Mt})),t.d(o,"ComponentButtonCarouselSliderDisabledOpacity",(function(){return $t})),t.d(o,"ComponentButtonCarouselSliderLightBackgroundColor",(function(){return Dt})),t.d(o,"ComponentButtonCarouselSliderWhiteBackgroundColor",(function(){return It})),t.d(o,"ComponentButtonDefaultFontSize",(function(){return Ut})),t.d(o,"ComponentButtonSmallFontSize",(function(){return Wt})),t.d(o,"ComponentButtonSmallHeight",(function(){return At})),t.d(o,"ComponentButtonSmallMinWidth",(function(){return Rt})),t.d(o,"ComponentButtonMediumFontSize",(function(){return Gt})),t.d(o,"ComponentButtonMediumHeight",(function(){return Xt})),t.d(o,"ComponentButtonMediumMinWidth",(function(){return Nt})),t.d(o,"ComponentButtonLargeFontSize",(function(){return Et})),t.d(o,"ComponentButtonLargeHeight",(function(){return Yt})),t.d(o,"ComponentButtonLargeMinWidth",(function(){return _t})),t.d(o,"ComponentButtonGoldBackgroundColor",(function(){return qt})),t.d(o,"ComponentButtonGoldColor",(function(){return Vt})),t.d(o,"ComponentButtonMaroonBackgroundColor",(function(){return Kt})),t.d(o,"ComponentButtonMaroonColor",(function(){return Jt})),t.d(o,"ComponentButtonDarkBackgroundColor",(function(){return Qt})),t.d(o,"ComponentButtonDarkColor",(function(){return Zt})),t.d(o,"ComponentButtonLightBackgroundColor",(function(){return no})),t.d(o,"ComponentButtonLightColor",(function(){return eo})),t.d(o,"ComponentCardBasicFontWeight",(function(){return to})),t.d(o,"ComponentCardBasicHeightPercent",(function(){return oo})),t.d(o,"ComponentCardBasicDisplay",(function(){return ro})),t.d(o,"ComponentCardBasicFlexDirection",(function(){return io})),t.d(o,"ComponentCardBasicHoverTransform",(function(){return ao})),t.d(o,"ComponentCardBasicHoverBoxShadow",(function(){return uo})),t.d(o,"ComponentCardBasicHoverCursor",(function(){return co})),t.d(o,"ComponentCardBasicActiveTransform",(function(){return so})),t.d(o,"ComponentCardBasicImageTopWidthPercent",(function(){return lo})),t.d(o,"ComponentCardBasicImageTopHeight",(function(){return fo})),t.d(o,"ComponentCardBasicImageTopHeightSm",(function(){return mo})),t.d(o,"ComponentCardBasicImageTopHeightLg",(function(){return po})),t.d(o,"ComponentCardBasicImageTopObjectFit",(function(){return go})),t.d(o,"ComponentCardBasicIconTopWidth",(function(){return ho})),t.d(o,"ComponentCardBasicIconTopHeight",(function(){return bo})),t.d(o,"ComponentCardBasicIconTopMargin",(function(){return Co})),t.d(o,"ComponentCardBasicIconTopMarginCentered",(function(){return Bo})),t.d(o,"ComponentCardBasicHeaderPadding",(function(){return yo})),t.d(o,"ComponentCardBasicHeaderPaddingSm",(function(){return Oo})),t.d(o,"ComponentCardBasicHeaderTextAlign",(function(){return xo})),t.d(o,"ComponentCardBasicHeaderTextAlignCentered",(function(){return So})),t.d(o,"ComponentCardBasicTitleLinkColor",(function(){return vo})),t.d(o,"ComponentCardBasicTitleLinkTextDecoration",(function(){return wo})),t.d(o,"ComponentCardBasicTitleLinkTextDecorationHover",(function(){return Lo})),t.d(o,"ComponentCardBasicBodyPadding",(function(){return Ho})),t.d(o,"ComponentCardBasicBodyPaddingSm",(function(){return jo})),t.d(o,"ComponentCardBasicButtonPadding",(function(){return ko})),t.d(o,"ComponentCardBasicButtonPaddingSm",(function(){return Po})),t.d(o,"ComponentCardBasicButtonWidthPercent",(function(){return Fo})),t.d(o,"ComponentCardBasicButtonMarginTop",(function(){return zo})),t.d(o,"ComponentCardBasicButtonAlignSelf",(function(){return To})),t.d(o,"ComponentCardBasicFooterAlignSelf",(function(){return Mo})),t.d(o,"ComponentCardBasicFooterLinkPadding",(function(){return $o})),t.d(o,"ComponentCardBasicFooterLinkPaddingSm",(function(){return Do})),t.d(o,"ComponentCardBasicFooterLinkBorderTop",(function(){return Io})),t.d(o,"ComponentCardDegreeTitleUnderlineWidth",(function(){return Uo})),t.d(o,"ComponentCardDegreeTitleUnderlineHeight",(function(){return Wo})),t.d(o,"ComponentCardDegreeTitleUnderlineContent",(function(){return Ao})),t.d(o,"ComponentCardDegreeTitleUnderlineDisplay",(function(){return Ro})),t.d(o,"ComponentCardDegreeTitleUnderlineColor",(function(){return Go})),t.d(o,"ComponentCardDegreeTitleUnderlineMarginTop",(function(){return Xo})),t.d(o,"ComponentCardStoryBodyMargin",(function(){return No})),t.d(o,"ComponentCardStoryBodyMarginSm",(function(){return Eo})),t.d(o,"ComponentCardStoryBackgroundColor",(function(){return Yo})),t.d(o,"ComponentHeaderBreakpointsMobile",(function(){return _o})),t.d(o,"ComponentHeaderLineHeight",(function(){return qo})),t.d(o,"ComponentHeadingFontFamily",(function(){return Vo})),t.d(o,"ComponentHeadingFontWeight",(function(){return Ko})),t.d(o,"ComponentHeadingTextAlign",(function(){return Jo})),t.d(o,"ComponentHeadingOpacity",(function(){return Qo})),t.d(o,"ComponentHeadingMargin",(function(){return Zo})),t.d(o,"ComponentHeadingLineHeightFormula",(function(){return nr})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeFirstOffsetX",(function(){return er})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeFirstOffsetY",(function(){return tr})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeFirstBlurRadius",(function(){return or})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeSecondOffsetX",(function(){return rr})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeSecondOffsetY",(function(){return ir})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeSecondBlurRadius",(function(){return ar})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallFirstOffsetX",(function(){return dr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallFirstOffsetY",(function(){return ur})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallFirstBlurRadius",(function(){return cr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallSecondOffsetX",(function(){return sr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallSecondOffsetY",(function(){return lr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallSecondBlurRadius",(function(){return fr})),t.d(o,"ComponentHeadingHighlightGoldBgColor",(function(){return mr})),t.d(o,"ComponentHeadingHighlightGoldTextColor",(function(){return pr})),t.d(o,"ComponentHeadingHighlightBlackBgColor",(function(){return gr})),t.d(o,"ComponentHeadingHighlightBlackTextColor",(function(){return hr})),t.d(o,"ComponentHeadingHighlightWhiteBgColor",(function(){return br})),t.d(o,"ComponentHeadingHighlightWhiteTextColor",(function(){return Cr})),t.d(o,"ComponentHeadingOneFontSize",(function(){return Br})),t.d(o,"ComponentHeadingOneLetterSpacing",(function(){return yr})),t.d(o,"ComponentHeadingOneArticleFontSize",(function(){return Or})),t.d(o,"ComponentHeadingOneMobileFontSize",(function(){return xr})),t.d(o,"ComponentHeadingTwoFontSize",(function(){return Sr})),t.d(o,"ComponentHeadingTwoLetterSpacing",(function(){return vr})),t.d(o,"ComponentHeadingTwoMobileFontSize",(function(){return wr})),t.d(o,"ComponentHeadingTwoMobileLetterSpacing",(function(){return Lr})),t.d(o,"ComponentHeadingThreeFontSize",(function(){return Hr})),t.d(o,"ComponentHeadingThreeLetterSpacing",(function(){return jr})),t.d(o,"ComponentHeadingFourFontSize",(function(){return kr})),t.d(o,"ComponentHeadingFourLetterSpacing",(function(){return Pr})),t.d(o,"ComponentHeadingFiveFontSize",(function(){return Fr})),t.d(o,"ComponentHeadingFiveLetterSpacing",(function(){return zr})),t.d(o,"ComponentHeroesContainerMdAndLgWidthPercent",(function(){return Tr})),t.d(o,"ComponentHeroesContainerMdAndLgUdsHeroTextLineHeight",(function(){return Mr})),t.d(o,"ComponentHeroesUdsHeroBackgroundSize",(function(){return $r})),t.d(o,"ComponentHeroesUdsHeroBackgroundPosition",(function(){return Dr})),t.d(o,"ComponentHeroesUdsHeroWidthPercent",(function(){return Ir})),t.d(o,"ComponentHeroesUdsHeroHeight",(function(){return Ur})),t.d(o,"ComponentHeroesUdsHeroDisplay",(function(){return Wr})),t.d(o,"ComponentHeroesUdsHeroMaxWidth",(function(){return Ar})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerWidthPx",(function(){return Rr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerDisplay",(function(){return Gr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerFlexDirection",(function(){return Xr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerAlignItems",(function(){return Nr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerMargin",(function(){return Er})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerH1MarginLeft",(function(){return Yr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerUdsHeroTextMarginLeft",(function(){return _r})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerPColor",(function(){return qr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerPFontSize",(function(){return Vr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerPMarginBottom",(function(){return Kr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroSmHeight",(function(){return Jr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroSmContainerUdsHeroContainerWidthPercent",(function(){return Qr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroMdHeight",(function(){return Zr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroLgHeight",(function(){return ni})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaBreakpoint",(function(){return ei})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaMarginBottom",(function(){return ti})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaH1MaxWidthPercent",(function(){return oi})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaPDisplay",(function(){return ri})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroSmBreakpoint",(function(){return ii})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroSmPaddingLeft",(function(){return ai})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroSmPaddingBottom",(function(){return di})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroLgBreakpoint",(function(){return ui})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroLgHeight",(function(){return ci})),t.d(o,"ComponentListSpacingPadding",(function(){return si})),t.d(o,"ComponentListSpacingListStyle",(function(){return li})),t.d(o,"ComponentListSpacingLiMaxWidth",(function(){return fi})),t.d(o,"ComponentListSpacingLiMarginBottom",(function(){return mi})),t.d(o,"ComponentListSpacingLiLastOfTypeMarginBottom",(function(){return pi})),t.d(o,"ComponentListUlStylesContentBullet",(function(){return gi})),t.d(o,"ComponentListUlStylesContentBulletEmpty",(function(){return hi})),t.d(o,"ComponentListUlStylesFontSize",(function(){return bi})),t.d(o,"ComponentListUlStylesVerticalAlign",(function(){return Ci})),t.d(o,"ComponentListUlStylesLineHeight",(function(){return Bi})),t.d(o,"ComponentListUlStylesPaddingRight",(function(){return yi})),t.d(o,"ComponentListUlStylesMarginLeft",(function(){return Oi})),t.d(o,"ComponentListUlStylesSubListPadding",(function(){return xi})),t.d(o,"ComponentListMaroonListColor",(function(){return Si})),t.d(o,"ComponentListDarkmodeMarginLeft",(function(){return vi})),t.d(o,"ComponentListDarkmodeMarginBottom",(function(){return wi})),t.d(o,"ComponentListDarkmodeBackgroundColor",(function(){return Li})),t.d(o,"ComponentListDarkmodeColor",(function(){return Hi})),t.d(o,"ComponentListDarkmodeLiBeforeColor",(function(){return ji})),t.d(o,"ComponentListDarkmodeGoldColor",(function(){return ki})),t.d(o,"ComponentListDarkmodeSteplistBackgroundColor",(function(){return Pi})),t.d(o,"ComponentListDarkmodeSteplistColor",(function(){return Fi})),t.d(o,"ComponentListSmokemodeMarginLeft",(function(){return zi})),t.d(o,"ComponentListSmokemodeMarginBottom",(function(){return Ti})),t.d(o,"ComponentListSmokemodeBackgroundColor",(function(){return Mi})),t.d(o,"ComponentListIconListMarginLeft",(function(){return $i})),t.d(o,"ComponentListIconListMarginBottom",(function(){return Di})),t.d(o,"ComponentListIconListPadding",(function(){return Ii})),t.d(o,"ComponentListIconListIconLeft",(function(){return Ui})),t.d(o,"ComponentListIconListLiBeforeContent",(function(){return Wi})),t.d(o,"ComponentListIconListLiBeforeFontSize",(function(){return Ai})),t.d(o,"ComponentListIconListLiBeforeVerticalAlign",(function(){return Ri})),t.d(o,"ComponentListIconListLiBeforeLineHeight",(function(){return Gi})),t.d(o,"ComponentListIconListLiBeforePaddingRight",(function(){return Xi})),t.d(o,"ComponentListIconListLiBeforeMarginLeft",(function(){return Ni})),t.d(o,"ComponentListIconListLiMaroonIcon",(function(){return Ei})),t.d(o,"ComponentListOlStylesNestedOlPadding",(function(){return Yi})),t.d(o,"ComponentListOlStylesLiBeforeLineHeight",(function(){return _i})),t.d(o,"ComponentListOlStylesLiBeforePaddingRight",(function(){return qi})),t.d(o,"ComponentListOlStylesLiBeforeMarginLeft",(function(){return Vi})),t.d(o,"ComponentListOlStylesLiNthOfType9MarginLeft",(function(){return Ki})),t.d(o,"ComponentListOlStylesLiNthOfType99MarginLeft",(function(){return Ji})),t.d(o,"ComponentListOlStylesSteplistStylesPaddingLeft",(function(){return Qi})),t.d(o,"ComponentListOlStylesSteplistStylesLiPaddingBottom",(function(){return Zi})),t.d(o,"ComponentListOlStylesSteplistStylesLiMarginBottom",(function(){return na})),t.d(o,"ComponentListOlStylesSteplistStylesLiBorderBottom",(function(){return ea})),t.d(o,"ComponentListOlStylesSteplistStylesLiFontWeight",(function(){return ta})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanPaddingLeft",(function(){return oa})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanDisplay",(function(){return ra})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanMarginTop",(function(){return ia})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanFontWeight",(function(){return aa})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeBorderRadius",(function(){return da})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeBackgroundColor",(function(){return ua})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeColor",(function(){return ca})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforePadding",(function(){return sa})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeMarginRight",(function(){return la})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeMarginLeft",(function(){return fa})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeFontSize",(function(){return ma})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeFontWeight",(function(){return pa})),t.d(o,"ComponentListOlStylesSteplistStylesGoldBackgroundColor",(function(){return ga})),t.d(o,"ComponentListOlStylesSteplistStylesGoldColor",(function(){return ha})),t.d(o,"ComponentListOlStylesSteplistStylesMaroonBackgroundColor",(function(){return ba})),t.d(o,"ComponentPagerColor",(function(){return Ca})),t.d(o,"ComponentPagerBorderWidth",(function(){return Ba})),t.d(o,"ComponentPagerBorderColor",(function(){return ya})),t.d(o,"ComponentPagerBorder",(function(){return Oa})),t.d(o,"ComponentPagerOutline",(function(){return xa})),t.d(o,"ComponentPagerBackgroundColor",(function(){return Sa})),t.d(o,"ComponentPagerBorderRadius",(function(){return va})),t.d(o,"ComponentPagerDisplay",(function(){return wa})),t.d(o,"ComponentPagerFontWeight",(function(){return La})),t.d(o,"ComponentPagerTextDecoration",(function(){return Ha})),t.d(o,"ComponentPagerLineHeight",(function(){return ja})),t.d(o,"ComponentPagerMaxWidth",(function(){return ka})),t.d(o,"ComponentPagerHoverStateTransform",(function(){return Pa})),t.d(o,"ComponentPagerActiveStateTransform",(function(){return Fa})),t.d(o,"ComponentPagerPadding",(function(){return za})),t.d(o,"ComponentPagerHoverTextDecoration",(function(){return Ta})),t.d(o,"ComponentPagerHoverColor",(function(){return Ma})),t.d(o,"ComponentPagerActiveBackgroundColor",(function(){return $a})),t.d(o,"ComponentPagerActiveColor",(function(){return Da})),t.d(o,"ComponentPagerDisabledOpacity",(function(){return Ia})),t.d(o,"ComponentPagerIconHeight",(function(){return Ua})),t.d(o,"ComponentPagerIconWidth",(function(){return Wa})),t.d(o,"ComponentPagerIconMargin",(function(){return Aa}));var r=t(0);const i=(n,e,t)=>Object(r.i)(Object(r.h)(n,e),t),a=(n,e,t)=>Object(r.k)(Object(r.h)(n,e),t),d=(n,e=!1,t="headerContainer")=>{const{loggedIn:o,userName:r,loginLink:d,...u}=n,c=d||(n=>{const e=window.location.toString();return n=(n=decodeURI(n)).replace("/login","/login?callapp="+e)})(mu.defaultProps.loginLink),s={...o&&r?{loggedIn:o,userName:r}:(()=>{let n={userName:"",loggedIn:!1};const e=document.cookie.split(";");for(let t=0;t<e.length;t++)if(e[t].indexOf("SSONAME")>0){if(""==e[t].substring(9))break;n.userName=e[t].substring(9),n.loggedIn=!0;break}return n})(),...u,loginLink:c};e?i(mu,s,document.getElementById(t)):a(mu,s,document.getElementById(t))};var u=t(3),c=t(2),s=t(1),l=t.n(s);const f="FontAwesome",m="assets/fontawesome/webfonts/fa-regular-400.ttf",p="assets/fontawesome/webfonts/fa-regular-400.eot",g="assets/fontawesome/webfonts/fa-regular-400.woff",h="assets/fontawesome/webfonts/fa-regular-400.woff2",b="assets/fontawesome/sprites/regular.svg",C="0",B="576px",y="768px",O="992px",x="1260px",S="1400px",v="1920px",w="#cc2f2f",L="#ff7f32",H="#00a3e0",j="#78be20",k="#ffffff",P="#e8e8e8",F="#191919",z="#e9f5db",T="#f7dddd",M="#ffeade",$="#d6f0fa",D="#191919",I="#ffc627",U="#8c1d40",W="#ffffff",A="#78be20",R="#ff7f32",G="#00a3e0",X="#00baff",N="#7f6227",E="#440e22",Y="#fafafa",_="#e8e8e8",q="#d0d0d0",V="#bfbfbf",K="#747474",J="#484848",Q="#191919",Z="#e8e8e8",nn="#d0d0d0",en="#bfbfbf",tn="#00baff",on="#cc2f2f",rn="#ff7f32",an="#78be20",dn="#00a3e0",un="#ffc627",cn="#8c1d40",sn="#191919",ln="#bfbfbf",fn="#191919",mn="#8c1d40",pn="#8c1d40",gn="#8c1d40",hn="#440e22",bn="#b72a2a",Cn="#bd4800",Bn="#446d12",yn="#126877",On="#fafafa",xn="#ffc627",Sn="#ffc627",vn="#ffc627",wn="#7f6227",Ln="#ff7b7d",Hn="#ff8034",jn="#78be20",kn="#00b0f3",Pn="#1e1e1e",Fn="#393939",zn="Arial, Helvetica, 'Nimbus Sans L', 'Liberation Sans', FreeSans, sans-serif",Tn="FontAwesome",Mn="100",$n="300",Dn="400",In="700",Un="900",Wn="400",An="540px",Rn="768px",Gn="992px",Xn="1224px",Nn="12",En="24px",Yn="34rem",_n="60rem",qn="75rem",Vn="0.75rem",Kn="0.875rem",Jn="1rem",Qn="1.25rem",Zn="1.5rem",ne="2rem",ee="3rem",te="1rem",oe="1.5rem",re="2rem",ie="2.5rem",ae="3rem",de="5rem",ue="0rem",ce="0.5rem",se="1rem",le="1.5rem",fe="2rem",me="2.5rem",pe="3rem",ge="3.5rem",he="4rem",be="4.5rem",Ce="5rem",Be="6rem",ye="7rem",Oe="8rem",xe="16rem",Se="32rem",ve="0.25rem",we="1rem",Le="400",He="700",je="200",ke="400",Pe="600",Fe="1000",ze="50",Te="100",Me="200",$e="2000",De="4000",Ie="6000",Ue="0.875rem",We=".75rem",Ae="1rem",Re="0.5rem",Ge="1rem",Xe="transparent",Ne="#bfbfbf",Ee="#191919",Ye="quote('/')",_e="none",qe="30px",Ve="0rem",Ke="0.5rem",Je="0.5rem",Qe="padding-box",Ze="0 0",nt="no-repeat",et="400rem",tt="block",ot="bold",rt="none",it="1rem",at="17.5rem",dt="scale(1.1)",ut="scale(1)",ct="1rem 2rem",st="1rem",lt="2rem",ft="0.5rem",mt="1rem",pt=".75rem",gt="0.25rem",ht="center",bt=".03s ease-in-out",Ct="50%",Bt="#bfbfbf",yt="400rem",Ot="normal",xt="1.375rem",St="2rem",vt="50%",wt="2rem",Lt="100%",Ht="#ffffff",jt="#bfbfbf",kt="1rem",Pt="1rem",Ft="#bfbfbf",zt="25%",Tt="#191919",Mt="#ffffff",$t="50%",Dt="#bfbfbf",It="#ffffff",Ut="1rem",Wt="0.75rem",At="1.375rem",Rt="4rem",Gt="0.875rem",Xt="2rem",Nt="5rem",Et="2rem",Yt="3rem",_t="8rem",qt="#ffc627",Vt="#191919",Kt="#8c1d40",Jt="#fafafa",Qt="#191919",Zt="#fafafa",no="#bfbfbf",eo="#191919",to="normal",oo="100%",ro="flex",io="column",ao="scale(1.05)",uo="0px 8px 16px rgba(25,25,25,0.2)",co="pointer",so="scale(1)",lo="100%",fo="12.5rem",mo="10rem",po="15rem",go="cover",ho="2rem",bo="2rem",Co="2rem 2rem 0 2rem",Bo="2rem auto 0 auto",yo="2rem",Oo="1.5rem",xo="left",So="center",vo="#191919",wo="none",Lo="underline",Ho="0 2rem 2rem 2rem",jo="0 1.5rem 1.5rem 1.5rem",ko="0 2rem 2rem 2rem",Po="0 1.5rem 1.5rem 1.5rem",Fo="100%",zo="auto",To="flex-end",Mo="flex-end",$o="1rem 2rem 1rem 2rem",Do="1rem 1rem 1rem 1rem",Io="1px solid rgba(0, 0, 0, 0.125)",Uo="2rem",Wo="0.25rem",Ao="''",Ro="block",Go="#ffc627",Xo="1rem",No="0 2rem 0 2rem",Eo="0 1rem 0 1rem",Yo="#ffffff",_o="60rem",qo="1.5rem",Vo="Arial, Helvetica, 'Nimbus Sans L', 'Liberation Sans', FreeSans, sans-serif",Ko="700",Jo="left",Qo="1",Zo="1rem",nr="calc(100% + .12em)",er="-0.15em",tr="0",or="0",rr="0.15em",ir="0",ar="0",dr="-0.15em",ur="0",cr="0",sr="0.15em",lr="0",fr="0",mr="#ffc627",pr="#191919",gr="#191919",hr="#fafafa",br="#ffffff",Cr="#191919",Br="4rem",yr="-0.035em",Or="3rem",xr="2.25rem",Sr="2.5rem",vr="-0.035em",wr="2rem",Lr="-0.035em",Hr="1.5rem",jr="-0.035em",kr="1.25rem",Pr="-0.025em",Fr="1rem",zr="-0.015em",Tr="100%",Mr="2rem",$r="cover",Dr="top",Ir="100%",Ur="42.75rem",Wr="flex",Ar="1920px",Rr="800px",Gr="flex",Xr="column",Nr="flex-start",Er="auto auto 2rem auto",Yr="0rem",_r="0rem",qr="#ffffff",Vr="1.5rem",Kr="1.75rem",Jr="16rem",Qr="100%",Zr="32rem",ni="42.75rem",ei="576px",ti="-2rem",oi="100%",ri="none",ii="576px",ai="1.5rem",di="2rem",ui="1400px",ci="32rem",si="3rem 5rem 3rem 2rem",li="none",fi="75rem",mi="1rem",pi="0rem",gi="\\2022 ",hi="\\25E6 ",bi="2rem",Ci="middle",Bi="1.5rem",yi="1.25rem",Oi="-2rem",xi="1rem 1.5rem 0rem",Si="#8c1d40",vi="0rem",wi="0rem",Li="#191919",Hi="#e8e8e8",ji="#e8e8e8",ki="#ffc627",Pi="#e8e8e8",Fi="#191919",zi="0rem",Ti="0rem",Mi="#e8e8e8",$i="0rem",Di="0rem",Ii="3rem 5rem",Ui="-2.5rem",Wi="none",Ai="2rem",Ri="middle",Gi="1.5rem",Xi="1rem",Ni="-1.5rem",Ei="#8c1d40",Yi="1rem 1.5rem 0rem",_i="1.5rem",qi="1rem",Vi="-1.9rem",Ki="-2.4rem",Ji="-2.9rem",Qi="1.5rem",Zi="2rem",na="3rem",ea="1px solid #bfbfbf",ta="bold",oa="0",ra="block",ia="1rem",aa="normal",da="50rem",ua="#191919",ca="#fafafa",sa="0.5rem 0.8rem",la="2rem",fa="-4.5rem",ma="1.25rem",pa="bold",ga="#ffc627",ha="#191919",ba="#8c1d40",Ca="#191919",Ba="0rem",ya="#000000",Oa="none",xa="0",Sa="#000000",va="400rem",wa="block",La="bold",Ha="none",ja="1rem",ka="17.5rem",Pa="scale(1.1)",Fa="scale(1)",za="1rem 2rem",Ta="underline",Ma="#ffffff",$a="#8c1d40",Da="#ffffff",Ia="50%",Ua="1rem",Wa="1rem",Aa="0.25rem",Ra=c.a`
  position: absolute;
  width: 1px;
  height: 1px;
  margin: -1px;
  padding: 0;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  border: 0;
`;c.a`
  :not(:focus):not(:active) {
    clip: rect(0 0 0 0);
    clip-path: inset(100%);
    height: 1px;
    overflow: hidden;
    position: absolute;
    white-space: nowrap;
    width: 1px;
  }
`;var Ga=o;const Xa=Object(u.b)((n,e)=>{const t="link"==n.type?"a":"button";return Object(r.h)(t,{class:Object(c.b)(c.a`
          text-decoration: none;
          font-weight: bold;
          display: inline-block;
          color: #191919;
          text-align: center;
          text-decoration: none;
          vertical-align: middle;
          user-select: none;
          background-color: transparent;
          border: 1px solid transparent;
          padding: 1rem 2rem;
          font-size: 1rem;
          line-height: 1rem;
          border-radius: 400rem;
          transition: 0.03s ease-in-out;

          :not(:disabled):not(.disabled) {
            cursor: pointer;
          }

        :hover {
          transform: ${Ga.ComponentButtonHoverStateTransform};
        }

        :active {
          transform: ${Ga.ComponentButtonActiveStateTransform};
        }

        ${n.disabled&&c.a`
            opacity: ${Ga.ComponentButtonDisabledOpacity};
          `}

        ${n.small&&c.a`
            font-size: ${Ga.ComponentButtonSmallFontSize};
            height: ${Ga.ComponentButtonSmallHeight};
            min-width: ${Ga.ComponentButtonSmallMinWidth};
            padding: ${Ga.ComponentButtonPaddingYSmall}
              ${Ga.ComponentButtonPaddingXSmall};
          `}

        ${n.medium&&c.a`
            font-size: 0.875rem;
            padding: 0.5rem 1rem;
          `}

        ${n.large&&c.a`
            font-size: ${Ga.ComponentButtonLargeFontSize};
            height: ${Ga.ComponentButtonLargeHeight};
            min-width: ${Ga.ComponentButtonLargeMinWidth};
          `}

        ${n.gold&&c.a`
            color: ${Ga.ComponentButtonGoldColor};
            background-color: ${Ga.ComponentButtonGoldBackgroundColor};

            :hover {
              color: ${Ga.ComponentButtonGoldColor};
            }
          `}

        ${n.maroon&&c.a`
            color: #ffffff;
            background-color: #8c1d40;
            border-color: #8c1d40;

            :visited:not(.btn) {
              color: #ffffff;
            }
          `}

        ${n.dark&&c.a`
            color: ${Ga.ComponentButtonDarkColor};
            background-color: ${Ga.ComponentButtonDarkBackgroundColor};
          `}

        ${n.light&&c.a`
            color: ${Ga.ComponentButtonLightColor};
            background-color: ${Ga.ComponentButtonLightBackgroundColor};
          `}
      `,n.class),onClick:n.onClick,href:n.href,ref:e},n.children)});Xa.propTypes={type:l.a.string,href:l.a.string,gold:l.a.bool,maroon:l.a.bool,disabled:l.a.bool,small:l.a.bool,medium:l.a.bool,large:l.a.bool,domRef:l.a.oneOfType([l.a.func,l.a.shape({current:l.a.instanceOf(l.a.element)})]),onFocus:l.a.func},Xa.defaultProps={disabled:!1};const Na=c.a`
  .btn {
    text-decoration: none;
    font-weight: bold;
    display: inline-block;
    color: #191919;
    text-align: center;
    text-decoration: none;
    vertical-align: middle;
    user-select: none;
    background-color: transparent;
    border: 1px solid transparent;
    padding: 1rem 2rem;
    font-size: 1rem;
    line-height: 1rem;
    border-radius: 400rem;
    transition: 0.03s ease-in-out;

    :not(:disabled):not(.disabled) {
      cursor: pointer;
    }

    :hover {
      transform: ${Ga.ComponentButtonHoverStateTransform};
    }

    :active {
      transform: ${Ga.ComponentButtonActiveStateTransform};
    }

    &.btn-disabled {
      opacity: ${Ga.ComponentButtonDisabledOpacity};
    }

    &.btn-small {
      font-size: ${Ga.ComponentButtonSmallFontSize};
      height: ${Ga.ComponentButtonSmallHeight};
      min-width: ${Ga.ComponentButtonSmallMinWidth};
      padding: ${Ga.ComponentButtonPaddingYSmall}
        ${Ga.ComponentButtonPaddingXSmall};
    }

    &.btn-medium {
      font-size: ${Ga.ComponentButtonMediumFontSize};
      height: ${Ga.ComponentButtonMediumHeight};
      min-width: ${Ga.ComponentButtonMediumMinWidth};
      padding: ${Ga.ComponentButtonPaddingYMedium}
        ${Ga.ComponentButtonPaddingXMedium};
    }

    &.btn-large {
      font-size: ${Ga.ComponentButtonLargeFontSize};
      height: ${Ga.ComponentButtonLargeHeight};
      min-width: ${Ga.ComponentButtonLargeMinWidth};
    }

    &.btn-gold {
      color: ${Ga.ComponentButtonGoldColor};
      background-color: ${Ga.ComponentButtonGoldBackgroundColor};
    }

    &.btn-maroon {
      color: ${Ga.ComponentButtonMaroonColor};
      background-color: ${Ga.ComponentButtonMaroonBackgroundColor};
    }

    &.btn-dark {
      color: ${Ga.ComponentButtonDarkColor};
      background-color: ${Ga.ComponentButtonDarkBackgroundColor};
    }

    &.btn-light {
      color: ${Ga.ComponentButtonLightColor};
      background-color: ${Ga.ComponentButtonLightBackgroundColor};
    }
  }
`;function Ea(){return(Ea=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Ya=Object(u.b)(({href:n,children:e,...t},o)=>{const i=n?"link":"button";return Object(r.h)(Xa,Ea({type:i,ref:o},n?{href:n}:{},t),e)});Ya.propTypes={type:l.a.string,href:l.a.string,gold:l.a.bool,maroon:l.a.bool,disabled:l.a.bool,small:l.a.bool,medium:l.a.bool,large:l.a.bool,itemRef:l.a.oneOfType([l.a.func,l.a.shape({current:l.a.instanceOf(l.a.element)})]),onFocus:l.a.func},Ya.defaultProps={disabled:!1};var _a=t(4),qa=t(5);function Va(){return(Va=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Ka=n=>Object(r.h)(_a.a,Va({icon:qa.a},n)),Ja=n=>Object(r.h)(_a.a,Va({icon:qa.l},n)),Qa=n=>Object(r.h)(_a.a,Va({icon:qa.c},n)),Za=n=>Object(r.h)(_a.a,Va({icon:qa.k},n)),nd=n=>Object(r.h)(_a.a,Va({icon:qa.f},n)),ed=n=>Object(r.h)(_a.a,Va({icon:qa.e},n)),td=n=>Object(r.h)(_a.a,Va({icon:qa.j},n)),od=n=>Object(r.h)(_a.a,Va({icon:qa.g},n)),rd=n=>Object(r.h)(_a.a,Va({icon:qa.b},n)),id=n=>Object(r.h)(_a.a,Va({icon:qa.i},n)),ad=n=>Object(r.h)("span",{class:Object(c.b)("fa-layers fa-fw",n.class)},Object(r.h)(_a.a,{icon:qa.d,size:"2x"}),Object(r.h)(_a.a,{icon:qa.m,size:"1x"})),dd=n=>Object(r.h)(_a.a,Va({icon:qa.h},n)),ud=({type:n,...e})=>{switch(n){case"mobile":return Object(r.h)(Za,null);case"chevron-down":return Object(r.h)(Qa,e);case"search":return Object(r.h)(Ja,e);case"desktop":return Object(r.h)(nd,e);case"clipboard":return Object(r.h)(ed,e);case"map-pin":return Object(r.h)(td,e);case"exclamation-triangle":return Object(r.h)(od,e);case"bell":return Object(r.h)(rd,e);case"info-circle":return Object(r.h)(id,e);case"circle-close":return Object(r.h)(ad,e);case"bars":return Object(r.h)(Ka,e);case"home":return Object(r.h)(dd,e);default:return""}};function cd(){return(cd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}ud.propTypes={type:l.a.string.isRequired},ud.defaultProps={};const sd=({show:n,id:e,...t})=>Object(r.h)("div",cd({},e?{id:e}:{},{class:Object(c.b)(c.a`
          padding: 0 32px 24px 32px;
          flex-grow: 100;
          flex: 1 1 auto;
          min-height: 1px;
          padding: 1.25rem;
          ${!n&&c.a`
            display: none;
          `}
        `,t.class),dangerouslySetInnerHTML:{__html:t.children}})),ld=n=>Object(r.h)("div",{class:Object(c.b)(c.a`
          position: relative;
          display: -webkit-box;
          display: -ms-flexbox;
          display: flex;
          flex-direction: column;
          min-width: 0;
          word-wrap: break-word;
          background-color: #ffffff;
          background-clip: border-box;
          border: 1px solid rgba(0, 0, 0, 0.125);
          border-radius: 0;
          border-color: #d0d0d0;
          border-left: 0.5rem solid #ffc627;
          height: auto;
        `,n.class)},n.children),fd=({show:n,id:e,...t})=>Object(r.h)(sd,cd({},e?{id:e}:{},{show:n,class:Object(c.b)(c.a`
          ${n&&c.a`
            border-top: 1px solid #d0d0d0;
          `}
        `,t.class)}),t.children),md=({show:n,id:e,...t})=>Object(r.h)("button",cd({"aria-expanded":n},e?{"aria-controls":e}:{},{role:"button",class:c.a`
        padding: 32px 32px 16px 32px;
        flex-grow: 1;
        padding-bottom: 0;
        padding: 0.75rem 1.25rem;
        margin-bottom: 0;
        background-color: rgba(255, 255, 255, 0.03);
        display: flex;
        flex-direction: row;
        align-items: baseline;
        justify-content: space-between;
        cursor: pointer;
        border: 0;

        h4 {
          display: flex;
          flex-direction: row;
          align-items: baseline;

          a {
            padding: 0.5rem 1.5rem;
            color: #191919;
            text-decoration: none;
            display: flex;
            flex-direction: row
            flex-wrap: nowrap;
            justify-content: space-between;
            align-items: center;
          }
        }

        .fa-chevron-down {
          transition-duration: 0.4s;
          font-size: 1.25rem;
        }

        ${n?c.a`
                .fa-chevron-down {
                  transform: rotate(-180deg);
                }
              `:""}

      `},t),t.children,Object(r.h)(ud,{type:"chevron-down"})),pd=({head:n,children:e,id:t,...o})=>{const[i,a]=Object(u.f)(!1);return Object(r.h)(ld,{class:o.class},Object(r.h)(md,{show:i,id:t,onClick:n=>{a(n=>!n)}},n),Object(r.h)(fd,{show:i,id:t},e))};function gd(){return(gd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}pd.propTypes={head:l.a.node,children:l.a.node,class:l.a.string,id:l.a.string},pd.defaultProps={};const hd=c.a`
  form.navbar-site-buttons {
    display: flex;
    align-items: flex-end;
    padding-bottom: 3px;


    a + a {
      margin-left: 1rem;
    }

    @media (max-width: ${"992px"}) {
      padding: 1rem 2rem;
    }
  }
`,bd=n=>Object(r.h)("form",{class:"navbar-site-buttons"},n.children),Cd=c.a`
  /** DdMenu CSS **/
  div.dropdown {
    display: none;
    z-index: 999;
    justify-content: space-between;
    background: #ffffff;
    flex-wrap: nowrap;
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
    margin: 0;
    padding: 1rem;
    border: 0;
    border-top: 1px solid #d0d0d0;

    &.open {
      display: flex;
    }

    h3 {
      font-size: 1.5rem;
      letter-spacing: -0.035em;
      font-weight: 700;
      text-align: left;
      opacity: 1;
      margin: 1rem 0;
      line-height: calc(100% + 0.12em);
    }

    > ul {
      display: flex;
      flex-direction: column;
      border-right: 1px solid #d0d0d0;
      padding: 0 2rem;
      margin-bottom: 3rem;

      :last-child {
        margin-bottom: 0;
        border-right: none;
      }

      @media (min-width: ${"992px"}) {
        width: 16rem;
        padding: 0 1.5rem 0 0;
        border-right: 1px solid #bfbfbf;
        margin-right: 1.5rem;

        :last-of-type {
          margin-right: 0;
          padding-right: 0;
          border-right: 0;
        }
      }

      > li {
        padding: 0.5rem 0;
      }
    }

    @media (max-width: ${"992px"}) {
      &.open {
        flex-direction: column;
        position: relative;
        padding-left: 3rem;
      }

      > ul {
        border-right: none;
        width: 100%;
        padding: 0;
        > li {
          border-bottom: 1px solid #cccccc;

          :last-of-type {
            border: none;
          }
        }
      }
    }

    @media (min-width: ${"992px"}) {
      margin: -1px 0 0 0;
      border: 1px solid #d0d0d0;
      border-top: 1px solid #ffffff;
      padding: 2rem;
      position: absolute;

      h3 {
        margin-top: 0;
      }

      > ul {
        width: 16rem;
        padding: 0 1.5rem 0 0;
        border-right: 1px solid #bfbfbf;
        margin-right: 1.5rem;

        > li {
          padding: 0;
          margin: 0;

          > .nav-item {
            padding: 0;
            padding: 0.5rem 0;
            white-space: normal;

            :visited {
              color: #191919;
            }

            :hover {
              color: #8c1d40;
              text-decoration: underline;
            }
          }
        }
      }
    }
  }
`,Bd=n=>Object(r.h)("div",{class:Object(c.b)("dropdown",n.open?"open":"")},n.children),yd=c.a`
  .nav-icon {
    color: #191919;
  }
`,Od=c.a`

  ul {
    list-style: none;
    a {
      text-decoration: none;
    }
  }

  > ul {
    margin: 0;
    padding: 0;
    display: flex;
    flex-direction: row;
    align-items: center;

    > li {
      > a {
        display: block;

        svg.fa-chevron-down{
          transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

          &.open {
            transform: rotate(180deg);
          }
        }

        @media (min-width: ${"992px"}) {
          :after {
            content: "";
            position: relative;
            display: block;
            height: 0.5rem;
            background-color: #ffc627;
            bottom: 0;
            width: 0;
            transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
            bottom: -8px;
            left: -8px;
          }

          :hover:after {
            width: 100%;
            width: calc(100% + 16px);
          }


        }
      }
    }

    li {
      position: relative;
      margin-right: 16px;

      a {

        padding: 8px;
        position: relative;

        &.nav-item {
          color: #191919;
          display: block;
        }
      }
    }
  }

  .mobile-only {
    ${Ra}
  }

  @media (min-width: ${"992px"}) {
    width: 100%;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    padding: 0;
    margin: 0;

    svg.fa-chevron-down {
      float: none;
      display: inline-block;
      font-size: 0.75rem;
      margin-left: 0.5rem;
    }
  }

  @media (max-width: ${"992px"}) {
    border: none;
    display: none;

    &.open-nav,
    &:target {
      flex-direction: column;
      width: 100%;
      overflow-y: scroll;
      display: flex;
    }

    .mobile-only {
      ${(n=>{const e=n||"relative";return c.a`
    width: auto;
    height: auto;
    margin: 0;
    overflow: visible;
    border: none;
    clip: auto;
    position: ${e};
  `})()}
    }

    .icon-nav-item {
      ${Ra}
    }

    > ul {
      flex-direction: column;
      align-items: stretch;
      div.open {
        flex-direction: column;
        position: relative;
      }

      > li {
        margin-right: 0;

        > a {
          padding: 1rem 2rem;
          justify-content: space-between;
          display: flex;
          border-bottom: 1px solid #cccccc;
          align-items: center;

          > svg {
            font-size: 1.25rem;
          }
        }

        :first-of-type {
          border-top: 1px solid #cccccc;
        }

        :last-of-type {
          border-bottom: none;
        }
      }
    }
  }
  }

  ${Cd}
  ${hd}
  ${yd};
`,xd=c.a`
  nav.header-nav {
    ${Od}
  }
`,Sd=({open:n,maxMobileHeight:e,injectStyles:t,children:o,...i})=>{const a=-1==e?"75vh":e+"px";return Object(r.h)("nav",gd({id:"asu-header-nav",class:Object(c.b)("header-nav",n?"open-nav":"",c.a`
          @media (max-width: ${"992px"}) {
            &.open-nav,
            &:target {
              flex-direction: column;
              width: 100%;

              max-height: ${a};
              display: flex;
            }
          }
        `,t?Od:"")},i),o)};function vd(){return(vd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const wd=c.a`
  .asu-search-form {
    > form {
      display: flex;
      flex-flow: row wrap;
      align-items: center;

      label {
        position: relative;
        margin-left: -95px;
        font-weight: 400;
        transition: all 0.5s;
        color: #747474;
        display: none;
      }

      > input {
        background: url('data:image/svg+xml;utf8,<svg aria-hidden="true" focusable="false" data-prefix="fas" data-icon="search" class="svg-inline--fa fa-search fa-w-16 " role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512"><path fill="currentColor" d="M505 442.7L405.3 343c-4.5-4.5-10.6-7-17-7H372c27.6-35.3 44-79.7 44-128C416 93.1 322.9 0 208 0S0 93.1 0 208s93.1 208 208 208c48.3 0 92.7-16.4 128-44v16.3c0 6.4 2.5 12.5 7 17l99.7 99.7c9.4 9.4 24.6 9.4 33.9 0l28.3-28.3c9.4-9.4 9.4-24.6.1-34zM208 336c-70.7 0-128-57.2-128-128 0-70.7 57.2-128 128-128 70.7 0 128 57.2 128 128 0 70.7-57.2 128-128 128z"></path></svg>') no-repeat 10px 50%;
        background-size: 12px;

      }
    }

    > a {
      display: inline-block;
      font-size: 0.75rem;
      color: #484848;
    }

    @media (max-width: ${"992px"}) {
      width: 100%;
      display: flex;
      order: -1;

      > form {
        width: 100%;
        display: flex;
        align-items: center;
        padding: 1rem 2rem;

        > input {
          padding: 0.5rem 2rem;
          display: flex;
          width: 100%;
          border: 0;
          background-color: #FFFFFF;
        }

        > button {
          font-size: 1rem;
          opacity: 0.75;
        }
      }

      > a {
        display: none;
      }

      button {
        width: 2.5rem;
        height: 2.5rem;
      }


    }

    button {
      font-size: 0.75rem;
      border: none;
      background: transparent;
      cursor: pointer;
      margin-right: -30px;
      z-index: 20;
      width: 1.5rem;
      height: 1.5rem;
      padding: 0;
    }

    @media (min-width: ${"992px"}) {
      > form {
        justify-content: flex-end;
      }

      input {
        background-size: 16px;
        width: 32px;
        cursor: pointer;
        font-size: 0.75rem;
        line-height: 0.75rem;
        border: 0;
        border-radius: 0;
        padding: 0.25rem;
        transition: all 0.5s;
      }

      .show-search-input {
        > input {
          display: inline-flex;
          width: 200px;
          color: #747474;
          background-color: #fff;
          cursor: auto;
          margin: 0.5rem 0;
          padding-left: 32px;
          visibility: visible;
          height: calc(1.5em + 0.75rem + 2px);

          :valid + label {
            display: none;
          }
        }

        label {
          display: block;
          margin-bottom: 0;
          font-size: inherit;
        }
      }
    }
  }
`,Ld=n=>Object(r.h)("div",vd({class:Object(c.b)("asu-search-form",n.class)},n),n.children),Hd=c.a`
  .login-status {
    font-size: 0.75rem;
    display: flex;
    align-items: center;
    margin-right: 0.5rem;
    padding: 0.25rem 0.5rem 0.25rem 0.5rem;


    > a, span {
      padding: 0;
      margin: 0;
      color: #484848;
      text-decoration: none;
    }
    .name {
      font-weight: 700;
    }

    .signout:before {
      content: "(";
      margin-left: 4px;
    }

    .signout:after {
      content: ") ";
    }


    @media (min-width: ${"992px"}) {
      margin-left: .5rem;
    }
  }
`,jd=n=>Object(r.h)("div",{class:Object(c.b)(n.class,"login-status")},n.children);function kd(){return(kd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Pd=({children:n,...e})=>Object(r.h)("header",kd({},e,{class:Object(c.b)(e.class,c.a`
          *,
          *:before,
          *:after {
            box-sizing: border-box;
          }

          :focus {
            outline: 0;
            box-shadow: 0 0 8px #00baff !important;
          }

          a {
            cursor: pointer;
            text-decoration: none;
          }

          padding: 0;
          display: flex;
          flex-direction: column;
          position: fixed;
          width: 100%;
          z-index: 999;
          background: #ffffff;
          border-bottom: 1px solid #d0d0d0;
          transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
          top: 0;
          left: 0;

          div,
          h1 {
            font-family: Arial, sans-serif;
          }

          &.scrolled {
            transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
          }

          @media (max-width: ${"992px"}) {
            &.scrolled .primary-nav .header-title h1 {
              font-size: 1rem;
            }
          }
        `,$d,xd,Na,Id,Wd,Td,wd,Rd,Hd,Fd)}),n),Fd=c.a`
  .navbar-toggler {
    padding: 0.25rem 0.75rem;
    font-size: 1.25rem;
    line-height: 1;
    background-color: transparent;
    border-radius: 400rem;
    outline: 0;
    color: #191919;
    border: 0;
    margin-right: 2rem;
    cursor: pointer;

    @media (min-width: ${"992px"}) {
      display: none;
    }
  }
`,zd=({mobileOpen:n,...e})=>Object(r.h)("button",kd({},e,{class:Object(c.b)(c.a`
          .fa-circle {
            color: #e8e8e8;
            font-size: 1rem;
            margin-left: -12px;
            height: 2em;
            width: 2.5em;
          }

          svg.svg-inline--fa.fa-times {
            height: 1em;
            width: 1.25em;
            margin-left: 7px;
          }
        `,"navbar-toggler")}),n?Object(r.h)(ud,{type:"circle-close"}):Object(r.h)(ud,{type:"bars",href:"#asu-header-nav"})),Td=c.a`
  .universal-nav {
    padding: 0 2rem;
    display: flex;
    justify-content: center;
    background-color: #e8e8e8;
    height: 24px;
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

    > div {
      width: 100%;
      max-width: ${"1224px"};
      display: flex;
      flex-wrap: wrap;
      align-items: center;
      justify-content: flex-end;

      > div {
        > a {
          display: inline-flex;
          font-size: 0.75rem;
          padding: 0.25rem 0.5rem;
          color: #484848;
          margin: 0;
        }
      }
    }

    @media (max-width: ${"992px"}) {
      display: none;
      padding: 0;
      transition: none;
      height: auto;

      &.mobile-open {
        z-index: 998;
        width 100%;
        display: flex;
        justify-content: center;
      }

      .nav-grid {
        display: grid;
        grid-template-columns: 1fr 1fr;
        grid-auto-flow: row;
        justify-items: start;
        width: 100%;

        > a, div {
          color: #191919;
          margin-right: 0;
          text-align: center;
          width: 100%;
          font-size: 0.875rem;
          padding: 1rem 1.5rem;
          border-top: 1px solid #d0d0d0;
          display:block;

          :nth-child(even) {
            border-left: 1px solid #d0d0d0;
          }
        }
      }

    }
  }

  @media (min-width: ${"992px"}) {
    &.scrolled .universal-nav {
      height: 0;
      overflow: hidden;
    }

    .universal-nav {
      &.search-open {
        height: 48px;
      }

      .nav-grid {
        display: flex;
      }
    }
  }
`,Md=n=>Object(r.h)("div",{class:Object(c.b)("universal-nav",n.open?"mobile-open":"",n.searchOpen?"search-open":""),ref:n.domRef},n.children),$d=c.a`
  .primary-nav {
    background-color: #ffffff;
    display: flex;
    width: 100%;
    padding-right: 12px;
    padding-left: 12px;
    margin-right: auto;
    margin-left: auto;
    max-width: ${"1224px"};

    > div {
      display: flex;
      flex-direction: row;
      width: 100%;
      align-items: flex-start;
      transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
      position: relative;
      align-items: center;
    }

    @media (max-width: ${"992px"}) {
      order: -1;
      display: flex;
      top: 0;
      width: 100%;
      height: auto;
      background-color: #ffffff;
      padding: 0;
      z-index: 1600;
      padding: ${"24px"} 0 0 0;

      > div {
        padding: 0;
        flex-wrap: wrap;
        justify-content: space-between;
      }
    }
  }
`,Dd=n=>Object(r.h)("div",{class:"primary-nav"},n.children),Id=c.a`
  .navbar-container {
    display: flex;
    width: 100%;
    flex-direction: column;
    align-items: flex-start;

    @media (max-width: ${"992px"}) {
      width: 100%;
    }
  }
`,Ud=n=>Object(r.h)("div",{class:Object(c.b)("navbar-container",n.class)},n.children),Wd=c.a`
  .navbar-brand {
    display: inline-block;
    padding-top: 0.3125rem;
    padding-bottom: 0.3125rem;
    margin-right: 1rem;
    font-size: 1.25rem;
    line-height: inherit;
    white-space: nowrap;
    padding: 0;
    margin: 0;

    .horiz {
      display: none;
      transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
    }

    .vert {
      @media (min-width: 992px) {
        display: block;
        height: 72px;
        width: auto;
        margin: 1.5rem 1rem 1.5rem 0;
      }
    }

    img {
      height: 80px;
    }

    @media (max-width: ${"992px"}) {
      img {
        float: none;
        height: 32px;
      }

      .vert {
        display: none;
      }
      .horiz {
        display: block;
        height: 32px;
        width: auto;
        margin-bottom: 1rem;
        margin-left: 2rem;
      }
    }
  }

  &.scrolled .primary-nav .navbar-brand d img {
    height: 64px;
  }

  @media (max-width: ${"992px"}) {
    &.scrolled .primary-nav .navbar-brand d img {
      height: 28px;
    }

    &.scrolled .navbar-brand .horiz {
      margin-bottom: 0.5rem;
    }
  }
`,Ad=n=>{const e=n.brandLink?n.brandLink:"https://asu.edu";return Object(r.h)("a",{href:e,class:"navbar-brand",ref:n.domRef},Object(r.h)("img",{class:"vert",src:n.src,alt:n.alt}),Object(r.h)("img",{class:"horiz",src:n.mobileSrc}))},Rd=c.a`
  .title {
    line-height: 1;
    font-size: 1rem;
    font-weight: 700;
    padding: 0 2rem 1.5rem 2rem;
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

    > a {
      display: none;
    }

    @media (min-width: ${"992px"}) {
      line-height: 1;
      margin: 1rem 0;
      font-weight: 700;
      padding: 0;

      > a {
        font-size: 1rem;
        margin-bottom: 0.5rem;
        display: block;
      }

      &.subdomain-name {
        font-size: 2rem;
        margin: 1.5rem 0 1rem 0;
        font-weight: 700;
      }

      .subdomain-name {
        font-size: 1.5rem;
        margin-bottom: 0;
      }
    }
  }

  &.scrolled .title {
    padding-bottom: 1rem;
  }

  @media (min-width: ${"992px"}) {
    &.scrolled .title.subdomain-name {
      font-size: 1.5rem;
    }

    &.scrolled .title {
      padding-bottom: 0;
    }
  }
`,Gd=Object(u.b)(({title:n,unit:e,...t},o)=>e?Object(r.h)("div",{class:"title",ref:o},Object(r.h)("a",{class:"unit-name"},e),Object(r.h)("span",{class:"subdomain-name"},n)):Object(r.h)("div",{class:"title subdomain-name",ref:o},n));function Xd(){return(Xd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Nd=c.a`
  font-weight: 700;
  text-align: left;
  opacity: 1;
  margin: 1rem 0;
  line-height: calc(100% + 0.12em);
`,Ed=({children:n,...e})=>Object(r.h)("h4",Xd({},e,{class:Object(c.b)(c.a`
          ${Nd}
          font-size: 1.25rem;
          letter-spacing: -0.025em;
        `,e.class)}),n),Yd=({children:n,...e})=>Object(r.h)("h3",Xd({},e,{class:Object(c.b)(c.a`
          ${Nd}
          font-size: 1.5rem;
          letter-spacing: -0.035em;
        `,e.class)}),n),_d=({type:n,...e})=>{switch(n){case"h4":return Object(r.h)(Ed,{class:e.class},e.children);case"h3":return Object(r.h)(Yd,{class:e.class},e.children);default:return""}};function qd(){return(qd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}_d.propTypes={type:l.a.string.isRequired},_d.defaultProps={};const Vd=({onFocus:n,itemRef:e,type:t,text:o,color:i,href:a,...d})=>{let u="";switch(t){case"button":u=Object(r.h)(Ya,qd({class:"nav-button",ref:e,href:a},n?{onFocus:n}:"",{medium:!0,dark:!0}),o);break;case"icon":u=Object(r.h)("a",qd({class:"nav-icon",href:a},n?{onFocus:n}:"",{ref:e}),Object(r.h)(ud,{type:d.class,className:"icon-nav-item"}),Object(r.h)("span",{class:"mobile-only"},o));break;case"heading":return Object(r.h)(_d,{type:"h3"},o);default:u=Object(r.h)("a",qd({class:"nav-item",href:a},n?{onFocus:n}:"",{ref:e}),o)}return Object(r.h)("li",null,u)};Vd.propTypes={itemRef:l.a.oneOfType([l.a.func,l.a.shape({current:l.a.instanceOf(l.a.element)})]),location:l.a.array,onFocus:l.a.func,type:l.a.string,href:l.a.string,text:l.a.string.isRequired,color:l.a.string,icon:l.a.string},Vd.defaultProps={};var Kd=Vd;const Jd=({item:n,submenus:e,mobileWidth:t,width:o,setFocus:i,pIndex:a,isOpen:d,setOpen:u,topRef:c,hasFocus:s,...l})=>{const f=n=>{u(d?-1:n)};return Object(r.h)("li",null,Object(r.h)("a",{target:n.target,title:n.title?n.title:n.text,role:"button","aria-expanded":d,onMouseDown:n=>{n.preventDefault(),f(a)},onKeyDown:n=>{const e=n.keyCode;32!=e&&13!=e||f(a)},onFocus:n=>{i([a,-1,-1])},tabIndex:"0",ref:c},n.text," ",Object(r.h)(Qa,{sr:n.text,className:d?"open":""})),Object(r.h)(Bd,{open:d},e.map((n,t)=>Object(r.h)("ul",null,n.map((n,o)=>Object(r.h)(Kd,{onFocus:()=>{i([a,t,o]),(n=>{u(n)})(a)},itemRef:e[t][o].ref,type:n.hasOwnProperty("type")?n.type:void 0,color:n.hasOwnProperty("color")?n.color:void 0,class:n.hasOwnProperty("class")?n.class:void 0,href:n.hasOwnProperty("href")?n.href:void 0,text:n.text}))))))};Jd.propTypes={setFocus:l.a.func,location:l.a.array,item:l.a.object.isRequired,submenus:l.a.arrayOf(l.a.arrayOf(l.a.object)).isRequired,topRef:l.a.oneOfType([l.a.func,l.a.shape({current:l.a.instanceOf(l.a.element)})]),mobileWidth:l.a.number,width:l.a.number,pIndex:l.a.number.isRequired,isOpen:l.a.bool,setOpen:l.a.func,hasFocus:l.a.bool},Jd.defaultProps={menus:[],top:!1,mobileWidth:992,isOpen:!1};var Qd=Jd;function Zd(){return(Zd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const nu=({navTree:n,width:e,height:t,mobileOpen:o,maxMobileHeight:i,buttons:a,injectStyles:d,...c})=>{const[s,l]=Object(u.f)([-1,-1,-1]),[f,m]=Object(u.f)(-1),p=n=>{l(n)},g=parseInt("992px",10),h=Object(u.d)(()=>n.map(n=>{const e=Object(r.g)();let t=[],{items:o,...i}=n;if(o&&o[0].length>0)for(let n=0;n<o.length;n++)for(let e=0;e<o[n].length;e++)if(t[n]||(t[n]=[]),t[n][e]=Object.assign({},o[n][e]),"heading"!=o[n][e].type){const o=Object(r.g)();t[n][e].ref=o}return{ref:e,item:i,menus:t}}),[n]);Object(u.c)(()=>{const n=eu(s,h);if(n.hasFocus){const[e,t,o]=s;n.isTop?h[e].ref&&h[e].ref.current.focus():h[e].menus[t][o].ref&&h[e].menus[t][o].ref.current.focus()}},[s,h]);const b=Object(u.e)(null);Object(u.c)(()=>{const n=n=>{b.current&&!b.current.contains(n.target)&&m(-1)};return document.addEventListener("mousedown",n),()=>{document.removeEventListener("mousedown",n)}},[b]);return Object(r.h)(Sd,{open:o,maxMobileHeight:i,injectStyles:d},Object(r.h)("ul",Zd({},e>g?{onfocusout:n=>{n.currentTarget.contains(n.relatedTarget)||p([-1,-1,-1])}}:{},{"aria-label":"ASU",onKeyDown:n=>{const e=eu(s,h);if(e.hasFocus)switch(n.keyCode){case 37:n.preventDefault(),p(tu(s,e,h));break;case 39:n.preventDefault(),p(ou(s,e,h));break;case 38:n.preventDefault(),p(ru(s,e,h));break;case 40:n.preventDefault(),p(iu(s,e,h));break;case 9:if(n.shiftKey){if(e.isFirst)return!1;n.preventDefault(),p(tu(s,e,h))}else{if(e.isLast)return!1;n.preventDefault(),p(ou(s,e,h))}}},ref:b}),h.map((n,t)=>{const o=n.item,i=n.menus;let a=!1;return f==t&&(a=!0),i&&i.length>0&&i[0].length>0?Object(r.h)(Qd,{width:e,item:o,submenus:i,pIndex:t,setFocus:p,topRef:n.ref,isOpen:a,setOpen:m,mobileWidth:g}):Object(r.h)(Kd,{onFocus:()=>{p([t,-1,-1])},itemRef:n.ref,type:o.hasOwnProperty("type")?o.type:void 0,color:o.hasOwnProperty("color")?o.color:void 0,class:o.hasOwnProperty("class")?o.class:"",href:o.hasOwnProperty("href")?o.href:void 0,text:o.text})})),a.length>0&&Object(r.h)(bd,null,a.map((n,e)=>{let t=n.color?n.color:"maroon";return Object(r.h)(Ya,Zd({href:n.href},{[t]:!0},{medium:!0}),n.text)})))};nu.propTypes={navTree:l.a.arrayOf(l.a.object),buttons:l.a.arrayOf(l.a.object),mobileOpen:l.a.bool,width:l.a.number,height:l.a.number,maxMobileHeight:l.a.number,injectStyles:l.a.bool},nu.defaultProps={navTree:[],mobileOpen:!1,width:1920,height:1080,maxMobileHeight:-1,buttons:[],injectStyles:!1};const eu=(n,e)=>{const[t,o,r]=n;let i=!1,a=!1,d=!1,u=!1,c=!1;return-1==t&&-1==o&&-1==r?{hasFocus:i}:(i=!0,e[t].menus.length>0&&(d=!0),a=-1===o||-1===r,a&&t===e.length-1&&(u=!0),a&&0===t&&(c=!0),{hasFocus:i,isTop:a,hasSubs:d,isLast:u,isFirst:c})},tu=(n,e,t)=>{const[o,r,i]=n;let a=n;return e.isTop?(a=void 0!==t[o-1]?[o-1,-1,-1]:[0,-1,-1],!1===au(a,t)?tu(a,eu(a,t),t):a):void 0!==t[o].menus[r-1]?t[o].menus[r-1][0].ref?[o,r-1,0]:[o,r-1,1]:[o,-1,-1]},ou=(n,e,t)=>{const[o,r,i]=n;let a=n;return e.isTop?(a=void 0!==t[o+1]?[o+1,-1,-1]:[t.length-1,-1,-1],!1===au(a,t)?ou(a,eu(a,t),t):a):void 0!==t[o].menus[r+1]?t[o].menus[r+1][0].ref?[o,r+1,0]:[o,r+1,1]:[o,-1,-1]},ru=(n,e,t)=>{const[o,r,i]=n;let a=[],d=n;return e.hasSubs&&(a=t[o].menus),d=e.isTop?tu(n,e,t):void 0!==a[r][i-1]?[o,r,i-1]:[o,-1,-1],!1===au(d,t)?ru(d,eu(d,t),t):d},iu=(n,e,t)=>{const[o,r,i]=n;let a=[],d=n;return e.hasSubs&&(a=t[o].menus),d=e.isTop&&e.hasSubs?[o,0,0]:e.isTop?ou(n,e,t):void 0!==a[r][i+1]?[o,r,i+1]:ou(n,e,t),!1===au(d,t)?iu(d,eu(d,t),t):d},au=(n,e)=>{const t=eu(n,e);if(!t.hasFocus)return!1;if(t.isTop){if(e[n[0]].ref)return!0}else if(e[n[0]].menus[n[1]][n[2]].ref)return!0;return!1};function du(){return(du=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const uu=({type:n,open:e,inputRef:t,mobile:o,...i})=>{switch(n){case"d7":return Object(r.h)("div",null,"Drupal 7");default:return Object(r.h)("form",{action:"https://search.asu.edu/search",method:"get",role:"search",class:e?"show-search-input":""},Object(r.h)("input",du({name:"q",type:"search"},t?{ref:t}:{},{"aria-labelledby":"asu-search-label"},o?{placeHolder:"Search ASU"}:{},{required:!0})),Object(r.h)("label",{class:"univeral-search",id:"asu-search-label"},"Search ASU"))}};uu.propTypes={type:l.a.string,open:l.a.bool,inputRef:l.a.oneOfType([l.a.func,l.a.shape({current:l.a.instanceOf(l.a.element)})]),mobile:l.a.bool},uu.defaultProps={};const cu=({type:n,open:e,setOpen:t,mobile:o})=>{const i=Object(u.e)(null);return Object(r.h)(Ld,{onfocusin:()=>t(!0),onfocusout:n=>{i.current.value||n.currentTarget.contains(n.relatedTarget)||t(!1)},onClick:n=>{t(!0),i.current.focus()}},Object(r.h)(uu,{open:e,type:n,inputRef:i,mobile:o}))};cu.propTypes={type:l.a.string,open:l.a.bool,setOpen:l.a.func,mobile:l.a.bool},cu.defaultProps={open:!1};const su=({loggedIn:n,loginLink:e,logoutLink:t,userName:o,...i})=>Object(r.h)(jd,{class:i.class},n?Object(r.h)(r.b,null,o?Object(r.h)("span",{class:"name"},o):"",Object(r.h)("a",{class:"signout",href:t},"Sign Out")):Object(r.h)("a",{href:e},"Sign in"));function lu(){const n="undefined"!=typeof window,{innerWidth:e,innerHeight:t}=n?window:{innerWidth:1920,innerHeight:1080};return{width:e,height:t}}function fu(){return(fu=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}su.propTypes={class:l.a.string,loggedIn:l.a.bool.isRequired,loginLink:l.a.string,logoutLink:l.a.string,userName:l.a.string},su.defaultProps={logoutLink:"https://webapp4.asu.edu/myasu/Signout",loginLink:"https://weblogin.asu.edu/cgi-bin/login",loggedIn:!1};const mu=({navTree:n,title:e,unit:t,logo:o,loggedIn:i,userName:a,loginLink:d,logoutLink:c,buttons:s,...l})=>{const[f,m]=Object(u.f)(!1),[p,g]=Object(u.f)(!1),[h,b]=Object(u.f)(-1),C=parseInt("992px",10),{height:B,width:y}=function(){const[n,e]=Object(u.f)(lu());return Object(u.c)(()=>{function n(){e(lu())}return window.addEventListener("resize",n),()=>window.removeEventListener("resize",n)},[]),n}(),[O,x]=Object(u.f)(0),S=()=>{const n=window.pageYOffset;x(n)};Object(u.c)(()=>(window.addEventListener("scroll",S,{passive:!0}),()=>{window.removeEventListener("scroll",S)}),[]);const v=parseInt("24px",10),w=Object(u.e)(null),L=Object(u.e)(null),H=Object(u.e)(null);return Object(u.c)(()=>{y<C&&f&&window.setTimeout(()=>{const n=w.current.clientHeight,e=L.current.clientHeight,t=H.current.clientHeight;b(B-n-(e+t+v))},500)},[B,y,f]),Object(r.h)(Pd,{class:O>0||f&&y<C?"scrolled":""},Object(r.h)(Md,fu({open:f,domRef:w},{searchOpen:p}),Object(r.h)("div",null,Object(r.h)("div",{class:"nav-grid"},Object(r.h)("a",{href:"https://www.asu.edu/"},"ASU home"),Object(r.h)("a",{href:"https://my.asu.edu/"},"My ASU"),Object(r.h)("a",{href:"https://www.asu.edu/colleges/"},"Colleges and schools"),Object(r.h)(su,{loggedIn:i,loginLink:d,logoutLink:c,userName:a})),Object(r.h)(cu,{open:p,setOpen:g,mobile:y<C}))),Object(r.h)(Dd,null,l.dangerouslyGenerateStub?Object(r.h)("div",{id:"asu-generated-stub"}):Object(r.h)("div",null,Object(r.h)(Ad,fu({},o,{domRef:L})),Object(r.h)(zd,{onClick:n=>{n.preventDefault(),m(n=>!n)},mobileOpen:f}),Object(r.h)(Ud,null,Object(r.h)(Gd,fu({title:e,unit:t},{ref:H})),Object(r.h)(nu,{navTree:n,logo:o,mobileOpen:f,height:B,width:y,buttons:s,maxMobileHeight:h})))))};mu.propTypes={navTree:l.a.arrayOf(l.a.object),logo:l.a.shape({alt:l.a.string,src:l.a.string,mobileSrc:l.a.string,brandLink:l.a.string}),title:l.a.string,unit:l.a.string,loggedIn:l.a.bool,userName:l.a.string,loginLink:l.a.string,logoutLink:l.a.string,buttons:l.a.arrayOf(l.a.object)},mu.defaultProps={navTree:[],dangerouslyGenerateStub:!1,logo:{alt:"Arizona State University Logo",src:"https://i.imgur.com/5WtkgkV.png",mobileSrc:"https://www.asu.edu/asuthemes/4.10/assets/arizona-state-university-logo.png"},title:"",unit:"",loggedIn:su.defaultProps.loggedIn,loginLink:su.defaultProps.loginLink,logoutLink:su.defaultProps.logoutLink,buttons:[]};const pu=n=>Object(r.h)("div",{class:Object(c.b)(n.class,c.a`
          padding: 2rem;
          margin-bottom: 2rem;
          border-radius: 0.3rem;
          border: 1px solid #dee2e6;
        `)},n.children),gu=n=>Object(r.h)(pu,{class:n.class},n.children);gu.propTypes={class:l.a.string},gu.defaultProps={}}})}));