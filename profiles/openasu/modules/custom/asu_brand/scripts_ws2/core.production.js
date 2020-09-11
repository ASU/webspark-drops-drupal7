!function(n,e){"object"==typeof exports&&"object"==typeof module?module.exports=e():"function"==typeof define&&define.amd?define("AsuWebcore",[],e):"object"==typeof exports?exports.AsuWebcore=e():n.AsuWebcore=e()}(window,(function(){return function(n){function e(e){for(var o,a,d=e[0],u=e[1],c=e[2],l=0,f=[];l<d.length;l++)a=d[l],Object.prototype.hasOwnProperty.call(r,a)&&r[a]&&f.push(r[a][0]),r[a]=0;for(o in u)Object.prototype.hasOwnProperty.call(u,o)&&(n[o]=u[o]);for(s&&s(e);f.length;)f.shift()();return i.push.apply(i,c||[]),t()}function t(){for(var n,e=0;e<i.length;e++){for(var t=i[e],o=!0,d=1;d<t.length;d++){var u=t[d];0!==r[u]&&(o=!1)}o&&(i.splice(e--,1),n=a(a.s=t[0]))}return n}var o={},r={0:0},i=[];function a(e){if(o[e])return o[e].exports;var t=o[e]={i:e,l:!1,exports:{}};return n[e].call(t.exports,t,t.exports,a),t.l=!0,t.exports}a.m=n,a.c=o,a.d=function(n,e,t){a.o(n,e)||Object.defineProperty(n,e,{enumerable:!0,get:t})},a.r=function(n){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(n,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(n,"__esModule",{value:!0})},a.t=function(n,e){if(1&e&&(n=a(n)),8&e)return n;if(4&e&&"object"==typeof n&&n&&n.__esModule)return n;var t=Object.create(null);if(a.r(t),Object.defineProperty(t,"default",{enumerable:!0,value:n}),2&e&&"string"!=typeof n)for(var o in n)a.d(t,o,function(e){return n[e]}.bind(null,o));return t},a.n=function(n){var e=n&&n.__esModule?function(){return n.default}:function(){return n};return a.d(e,"a",e),e},a.o=function(n,e){return Object.prototype.hasOwnProperty.call(n,e)},a.p="";var d=window.webpackJsonpAsuWeb_name_=window.webpackJsonpAsuWeb_name_||[],u=d.push.bind(d);d.push=e,d=d.slice();for(var c=0;c<d.length;c++)e(d[c]);var s=u;return i.push([13,1]),t()}({13:function(n,e,t){"use strict";t.r(e),t.d(e,"Button",(function(){return _a})),t.d(e,"FoldableCard",(function(){return gd})),t.d(e,"Header",(function(){return pu})),t.d(e,"Heading",(function(){return qd})),t.d(e,"Icon",(function(){return cd})),t.d(e,"Nav",(function(){return eu})),t.d(e,"Panel",(function(){return hu})),t.d(e,"HydratePreact",(function(){return i})),t.d(e,"RenderPreact",(function(){return a})),t.d(e,"initHeader",(function(){return u})),t.d(e,"checkSSOCookie",(function(){return d}));var o={};t.r(o),t.d(o,"AssetFontIconName",(function(){return m})),t.d(o,"AssetFontIconTtf",(function(){return p})),t.d(o,"AssetFontIconEot",(function(){return g})),t.d(o,"AssetFontIconWoff",(function(){return h})),t.d(o,"AssetFontIconWoff2",(function(){return b})),t.d(o,"AssetFontIconSvg",(function(){return C})),t.d(o,"BreakpointXs",(function(){return B})),t.d(o,"BreakpointSm",(function(){return y})),t.d(o,"BreakpointMd",(function(){return O})),t.d(o,"BreakpointLg",(function(){return x})),t.d(o,"BreakpointXl",(function(){return S})),t.d(o,"BreakpointXxl",(function(){return v})),t.d(o,"BreakpointXxxl",(function(){return w})),t.d(o,"ColorAlertsError",(function(){return L})),t.d(o,"ColorAlertsWarning",(function(){return H})),t.d(o,"ColorAlertsInfo",(function(){return j})),t.d(o,"ColorAlertsSuccess",(function(){return k})),t.d(o,"ColorBackgroundWhite",(function(){return P})),t.d(o,"ColorBackgroundGray",(function(){return F})),t.d(o,"ColorBackgroundDark",(function(){return z})),t.d(o,"ColorBackgroundSuccess",(function(){return T})),t.d(o,"ColorBackgroundError",(function(){return M})),t.d(o,"ColorBackgroundWarning",(function(){return $})),t.d(o,"ColorBackgroundInfo",(function(){return D})),t.d(o,"ColorBackgroundOverlay",(function(){return I})),t.d(o,"ColorBaseGold",(function(){return U})),t.d(o,"ColorBaseMaroon",(function(){return W})),t.d(o,"ColorBaseWhite",(function(){return A})),t.d(o,"ColorBaseGreen",(function(){return R})),t.d(o,"ColorBaseOrange",(function(){return G})),t.d(o,"ColorBaseBlue",(function(){return X})),t.d(o,"ColorBaseBluefocus",(function(){return N})),t.d(o,"ColorBaseDarkgold",(function(){return E})),t.d(o,"ColorBaseDarkmaroon",(function(){return Y})),t.d(o,"ColorBaseGray1",(function(){return _})),t.d(o,"ColorBaseGray2",(function(){return q})),t.d(o,"ColorBaseGray3",(function(){return V})),t.d(o,"ColorBaseGray4",(function(){return K})),t.d(o,"ColorBaseGray5",(function(){return J})),t.d(o,"ColorBaseGray6",(function(){return Q})),t.d(o,"ColorBaseGray7",(function(){return Z})),t.d(o,"ColorBorderLight",(function(){return nn})),t.d(o,"ColorBorderBase",(function(){return en})),t.d(o,"ColorBorderDark",(function(){return tn})),t.d(o,"ColorBorderFocus",(function(){return on})),t.d(o,"ColorBorderError",(function(){return rn})),t.d(o,"ColorBorderWarning",(function(){return an})),t.d(o,"ColorBorderSuccess",(function(){return dn})),t.d(o,"ColorBorderInfo",(function(){return un})),t.d(o,"ColorBrandGold",(function(){return cn})),t.d(o,"ColorBrandMaroon",(function(){return sn})),t.d(o,"ColorBrandDark",(function(){return ln})),t.d(o,"ColorBrandLight",(function(){return fn})),t.d(o,"ColorFontDarkBase",(function(){return mn})),t.d(o,"ColorFontDarkLink",(function(){return pn})),t.d(o,"ColorFontDarkHover",(function(){return gn})),t.d(o,"ColorFontDarkActive",(function(){return hn})),t.d(o,"ColorFontDarkVisited",(function(){return bn})),t.d(o,"ColorFontDarkError",(function(){return Cn})),t.d(o,"ColorFontDarkWarning",(function(){return Bn})),t.d(o,"ColorFontDarkSuccess",(function(){return yn})),t.d(o,"ColorFontDarkInfo",(function(){return On})),t.d(o,"ColorFontLightBase",(function(){return xn})),t.d(o,"ColorFontLightLink",(function(){return Sn})),t.d(o,"ColorFontLightHover",(function(){return vn})),t.d(o,"ColorFontLightActive",(function(){return wn})),t.d(o,"ColorFontLightVisited",(function(){return Ln})),t.d(o,"ColorFontLightError",(function(){return Hn})),t.d(o,"ColorFontLightWarning",(function(){return jn})),t.d(o,"ColorFontLightSuccess",(function(){return kn})),t.d(o,"ColorFontLightInfo",(function(){return Pn})),t.d(o,"ColorDividerDarker",(function(){return Fn})),t.d(o,"ColorDividerLighter",(function(){return zn})),t.d(o,"FontFamilyBase",(function(){return Tn})),t.d(o,"FontFamilyIcons",(function(){return Mn})),t.d(o,"FontWeightLighter",(function(){return $n})),t.d(o,"FontWeightLight",(function(){return Dn})),t.d(o,"FontWeightNormal",(function(){return In})),t.d(o,"FontWeightBold",(function(){return Un})),t.d(o,"FontWeightBolder",(function(){return Wn})),t.d(o,"FontWeightBase",(function(){return An})),t.d(o,"GridContainerMaxWidthSm",(function(){return Rn})),t.d(o,"GridContainerMaxWidthMd",(function(){return Gn})),t.d(o,"GridContainerMaxWidthLg",(function(){return Xn})),t.d(o,"GridContainerMaxWidthXl",(function(){return Nn})),t.d(o,"GridColumnCount",(function(){return En})),t.d(o,"GridGutterWidth",(function(){return Yn})),t.d(o,"SizeBreakpointsSmall",(function(){return _n})),t.d(o,"SizeBreakpointsMedium",(function(){return qn})),t.d(o,"SizeBreakpointsLarge",(function(){return Vn})),t.d(o,"SizeFontTiny",(function(){return Kn})),t.d(o,"SizeFontSmall",(function(){return Jn})),t.d(o,"SizeFontMedium",(function(){return Qn})),t.d(o,"SizeFontLarge",(function(){return Zn})),t.d(o,"SizeFontXl",(function(){return ne})),t.d(o,"SizeFontXxl",(function(){return ee})),t.d(o,"SizeFontXxxl",(function(){return te})),t.d(o,"SizeFontBase",(function(){return oe})),t.d(o,"SizeIconSmall",(function(){return re})),t.d(o,"SizeIconBase",(function(){return ie})),t.d(o,"SizeIconLarge",(function(){return ae})),t.d(o,"SizeIconXl",(function(){return de})),t.d(o,"SizeIconXxl",(function(){return ue})),t.d(o,"SizeSpacing0",(function(){return ce})),t.d(o,"SizeSpacing1",(function(){return se})),t.d(o,"SizeSpacing2",(function(){return le})),t.d(o,"SizeSpacing3",(function(){return fe})),t.d(o,"SizeSpacing4",(function(){return me})),t.d(o,"SizeSpacing5",(function(){return pe})),t.d(o,"SizeSpacing6",(function(){return ge})),t.d(o,"SizeSpacing7",(function(){return he})),t.d(o,"SizeSpacing8",(function(){return be})),t.d(o,"SizeSpacing9",(function(){return Ce})),t.d(o,"SizeSpacing10",(function(){return Be})),t.d(o,"SizeSpacing12",(function(){return ye})),t.d(o,"SizeSpacing14",(function(){return Oe})),t.d(o,"SizeSpacing16",(function(){return xe})),t.d(o,"SizeSpacing32",(function(){return Se})),t.d(o,"SizeSpacing64",(function(){return ve})),t.d(o,"SizeSpacingHalf",(function(){return we})),t.d(o,"SizeSpacingBase",(function(){return Le})),t.d(o,"WeightFontRegular",(function(){return He})),t.d(o,"WeightFontBold",(function(){return je})),t.d(o,"TimeTransitionShort",(function(){return ke})),t.d(o,"TimeTransitionBase",(function(){return Pe})),t.d(o,"TimeTransitionLong",(function(){return Fe})),t.d(o,"TimeTransitionXl",(function(){return ze})),t.d(o,"TimeDelayShort",(function(){return Te})),t.d(o,"TimeDelayBase",(function(){return Me})),t.d(o,"TimeDelayLong",(function(){return $e})),t.d(o,"TimeDurationShort",(function(){return De})),t.d(o,"TimeDurationBase",(function(){return Ie})),t.d(o,"TimeDurationLong",(function(){return Ue})),t.d(o,"ComponentBreadcrumbFontSize",(function(){return We})),t.d(o,"ComponentBreadcrumbPaddingY",(function(){return Ae})),t.d(o,"ComponentBreadcrumbPaddingX",(function(){return Re})),t.d(o,"ComponentBreadcrumbItemPadding",(function(){return Ge})),t.d(o,"ComponentBreadcrumbMarginBottom",(function(){return Xe})),t.d(o,"ComponentBreadcrumbBg",(function(){return Ne})),t.d(o,"ComponentBreadcrumbDividerColor",(function(){return Ee})),t.d(o,"ComponentBreadcrumbActiveColor",(function(){return Ye})),t.d(o,"ComponentBreadcrumbDivider",(function(){return _e})),t.d(o,"ComponentBreadcrumbBorderRadiusNone",(function(){return qe})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemPaddingLeftPx",(function(){return Ve})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemFirstOfTypePaddingLeft",(function(){return Ke})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemPlusBreadcrumbItemBeforePaddingLeft",(function(){return Je})),t.d(o,"ComponentBreadcrumbOlBreadcrumbBreadcrumbItemPlusBreadcrumbItemBeforePaddingRight",(function(){return Qe})),t.d(o,"ComponentButtonBackgroundOrigin",(function(){return Ze})),t.d(o,"ComponentButtonBackgroundPosition",(function(){return nt})),t.d(o,"ComponentButtonBackgroundRepeat",(function(){return et})),t.d(o,"ComponentButtonBorderRadius",(function(){return tt})),t.d(o,"ComponentButtonDisplay",(function(){return ot})),t.d(o,"ComponentButtonFontWeight",(function(){return rt})),t.d(o,"ComponentButtonTextDecoration",(function(){return it})),t.d(o,"ComponentButtonLineHeight",(function(){return at})),t.d(o,"ComponentButtonMaxWidth",(function(){return dt})),t.d(o,"ComponentButtonHoverStateTransform",(function(){return ut})),t.d(o,"ComponentButtonActiveStateTransform",(function(){return ct})),t.d(o,"ComponentButtonPadding",(function(){return st})),t.d(o,"ComponentButtonPaddingY",(function(){return lt})),t.d(o,"ComponentButtonPaddingX",(function(){return ft})),t.d(o,"ComponentButtonPaddingYMedium",(function(){return mt})),t.d(o,"ComponentButtonPaddingXMedium",(function(){return pt})),t.d(o,"ComponentButtonPaddingXSmall",(function(){return gt})),t.d(o,"ComponentButtonPaddingYSmall",(function(){return ht})),t.d(o,"ComponentButtonTextAlign",(function(){return bt})),t.d(o,"ComponentButtonTransition",(function(){return Ct})),t.d(o,"ComponentButtonDisabledOpacity",(function(){return Bt})),t.d(o,"ComponentButtonBadgeBackgroundColor",(function(){return yt})),t.d(o,"ComponentButtonBadgeBorderRadius",(function(){return Ot})),t.d(o,"ComponentButtonBadgeFontWeight",(function(){return xt})),t.d(o,"ComponentButtonBadgeHeight",(function(){return St})),t.d(o,"ComponentButtonCloseHeight",(function(){return vt})),t.d(o,"ComponentButtonCloseOpacity",(function(){return wt})),t.d(o,"ComponentButtonCloseWidth",(function(){return Lt})),t.d(o,"ComponentButtonCloseDisabledOpacity",(function(){return Ht})),t.d(o,"ComponentButtonCloseWhiteBackgroundColor",(function(){return jt})),t.d(o,"ComponentButtonCloseGrayBackgroundColor",(function(){return kt})),t.d(o,"ComponentButtonCarouselPositionHeight",(function(){return Pt})),t.d(o,"ComponentButtonCarouselPositionWidth",(function(){return Ft})),t.d(o,"ComponentButtonCarouselPositionInactiveBackgroundColor",(function(){return zt})),t.d(o,"ComponentButtonCarouselPositionInactiveOpacity",(function(){return Tt})),t.d(o,"ComponentButtonCarouselPositionBlackBackgroundColor",(function(){return Mt})),t.d(o,"ComponentButtonCarouselPositionWhiteBackgroundColor",(function(){return $t})),t.d(o,"ComponentButtonCarouselSliderDisabledOpacity",(function(){return Dt})),t.d(o,"ComponentButtonCarouselSliderLightBackgroundColor",(function(){return It})),t.d(o,"ComponentButtonCarouselSliderWhiteBackgroundColor",(function(){return Ut})),t.d(o,"ComponentButtonDefaultFontSize",(function(){return Wt})),t.d(o,"ComponentButtonSmallFontSize",(function(){return At})),t.d(o,"ComponentButtonSmallHeight",(function(){return Rt})),t.d(o,"ComponentButtonSmallMinWidth",(function(){return Gt})),t.d(o,"ComponentButtonMediumFontSize",(function(){return Xt})),t.d(o,"ComponentButtonMediumHeight",(function(){return Nt})),t.d(o,"ComponentButtonMediumMinWidth",(function(){return Et})),t.d(o,"ComponentButtonLargeFontSize",(function(){return Yt})),t.d(o,"ComponentButtonLargeHeight",(function(){return _t})),t.d(o,"ComponentButtonLargeMinWidth",(function(){return qt})),t.d(o,"ComponentButtonGoldBackgroundColor",(function(){return Vt})),t.d(o,"ComponentButtonGoldColor",(function(){return Kt})),t.d(o,"ComponentButtonMaroonBackgroundColor",(function(){return Jt})),t.d(o,"ComponentButtonMaroonColor",(function(){return Qt})),t.d(o,"ComponentButtonDarkBackgroundColor",(function(){return Zt})),t.d(o,"ComponentButtonDarkColor",(function(){return no})),t.d(o,"ComponentButtonLightBackgroundColor",(function(){return eo})),t.d(o,"ComponentButtonLightColor",(function(){return to})),t.d(o,"ComponentCardBasicFontWeight",(function(){return oo})),t.d(o,"ComponentCardBasicHeightPercent",(function(){return ro})),t.d(o,"ComponentCardBasicDisplay",(function(){return io})),t.d(o,"ComponentCardBasicFlexDirection",(function(){return ao})),t.d(o,"ComponentCardBasicHoverTransform",(function(){return uo})),t.d(o,"ComponentCardBasicHoverBoxShadow",(function(){return co})),t.d(o,"ComponentCardBasicHoverCursor",(function(){return so})),t.d(o,"ComponentCardBasicActiveTransform",(function(){return lo})),t.d(o,"ComponentCardBasicImageTopWidthPercent",(function(){return fo})),t.d(o,"ComponentCardBasicImageTopHeight",(function(){return mo})),t.d(o,"ComponentCardBasicImageTopHeightSm",(function(){return po})),t.d(o,"ComponentCardBasicImageTopHeightLg",(function(){return go})),t.d(o,"ComponentCardBasicImageTopObjectFit",(function(){return ho})),t.d(o,"ComponentCardBasicIconTopWidth",(function(){return bo})),t.d(o,"ComponentCardBasicIconTopHeight",(function(){return Co})),t.d(o,"ComponentCardBasicIconTopMargin",(function(){return Bo})),t.d(o,"ComponentCardBasicIconTopMarginCentered",(function(){return yo})),t.d(o,"ComponentCardBasicHeaderPadding",(function(){return Oo})),t.d(o,"ComponentCardBasicHeaderPaddingSm",(function(){return xo})),t.d(o,"ComponentCardBasicHeaderTextAlign",(function(){return So})),t.d(o,"ComponentCardBasicHeaderTextAlignCentered",(function(){return vo})),t.d(o,"ComponentCardBasicTitleLinkColor",(function(){return wo})),t.d(o,"ComponentCardBasicTitleLinkTextDecoration",(function(){return Lo})),t.d(o,"ComponentCardBasicTitleLinkTextDecorationHover",(function(){return Ho})),t.d(o,"ComponentCardBasicBodyPadding",(function(){return jo})),t.d(o,"ComponentCardBasicBodyPaddingSm",(function(){return ko})),t.d(o,"ComponentCardBasicButtonPadding",(function(){return Po})),t.d(o,"ComponentCardBasicButtonPaddingSm",(function(){return Fo})),t.d(o,"ComponentCardBasicButtonWidthPercent",(function(){return zo})),t.d(o,"ComponentCardBasicButtonMarginTop",(function(){return To})),t.d(o,"ComponentCardBasicButtonAlignSelf",(function(){return Mo})),t.d(o,"ComponentCardBasicFooterAlignSelf",(function(){return $o})),t.d(o,"ComponentCardBasicFooterLinkPadding",(function(){return Do})),t.d(o,"ComponentCardBasicFooterLinkPaddingSm",(function(){return Io})),t.d(o,"ComponentCardBasicFooterLinkBorderTop",(function(){return Uo})),t.d(o,"ComponentCardDegreeTitleUnderlineWidth",(function(){return Wo})),t.d(o,"ComponentCardDegreeTitleUnderlineHeight",(function(){return Ao})),t.d(o,"ComponentCardDegreeTitleUnderlineContent",(function(){return Ro})),t.d(o,"ComponentCardDegreeTitleUnderlineDisplay",(function(){return Go})),t.d(o,"ComponentCardDegreeTitleUnderlineColor",(function(){return Xo})),t.d(o,"ComponentCardDegreeTitleUnderlineMarginTop",(function(){return No})),t.d(o,"ComponentCardStoryBodyMargin",(function(){return Eo})),t.d(o,"ComponentCardStoryBodyMarginSm",(function(){return Yo})),t.d(o,"ComponentCardStoryBackgroundColor",(function(){return _o})),t.d(o,"ComponentHeaderBreakpointsMobile",(function(){return qo})),t.d(o,"ComponentHeaderLineHeight",(function(){return Vo})),t.d(o,"ComponentHeadingFontFamily",(function(){return Ko})),t.d(o,"ComponentHeadingFontWeight",(function(){return Jo})),t.d(o,"ComponentHeadingTextAlign",(function(){return Qo})),t.d(o,"ComponentHeadingOpacity",(function(){return Zo})),t.d(o,"ComponentHeadingMargin",(function(){return nr})),t.d(o,"ComponentHeadingLineHeightFormula",(function(){return er})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeFirstOffsetX",(function(){return tr})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeFirstOffsetY",(function(){return or})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeFirstBlurRadius",(function(){return rr})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeSecondOffsetX",(function(){return ir})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeSecondOffsetY",(function(){return ar})),t.d(o,"ComponentHeadingHighlightBoxShadowLargeSecondBlurRadius",(function(){return dr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallFirstOffsetX",(function(){return ur})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallFirstOffsetY",(function(){return cr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallFirstBlurRadius",(function(){return sr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallSecondOffsetX",(function(){return lr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallSecondOffsetY",(function(){return fr})),t.d(o,"ComponentHeadingHighlightBoxShadowSmallSecondBlurRadius",(function(){return mr})),t.d(o,"ComponentHeadingHighlightGoldBgColor",(function(){return pr})),t.d(o,"ComponentHeadingHighlightGoldTextColor",(function(){return gr})),t.d(o,"ComponentHeadingHighlightBlackBgColor",(function(){return hr})),t.d(o,"ComponentHeadingHighlightBlackTextColor",(function(){return br})),t.d(o,"ComponentHeadingHighlightWhiteBgColor",(function(){return Cr})),t.d(o,"ComponentHeadingHighlightWhiteTextColor",(function(){return Br})),t.d(o,"ComponentHeadingOneFontSize",(function(){return yr})),t.d(o,"ComponentHeadingOneLetterSpacing",(function(){return Or})),t.d(o,"ComponentHeadingOneArticleFontSize",(function(){return xr})),t.d(o,"ComponentHeadingOneMobileFontSize",(function(){return Sr})),t.d(o,"ComponentHeadingTwoFontSize",(function(){return vr})),t.d(o,"ComponentHeadingTwoLetterSpacing",(function(){return wr})),t.d(o,"ComponentHeadingTwoMobileFontSize",(function(){return Lr})),t.d(o,"ComponentHeadingTwoMobileLetterSpacing",(function(){return Hr})),t.d(o,"ComponentHeadingThreeFontSize",(function(){return jr})),t.d(o,"ComponentHeadingThreeLetterSpacing",(function(){return kr})),t.d(o,"ComponentHeadingFourFontSize",(function(){return Pr})),t.d(o,"ComponentHeadingFourLetterSpacing",(function(){return Fr})),t.d(o,"ComponentHeadingFiveFontSize",(function(){return zr})),t.d(o,"ComponentHeadingFiveLetterSpacing",(function(){return Tr})),t.d(o,"ComponentHeroesContainerMdAndLgWidthPercent",(function(){return Mr})),t.d(o,"ComponentHeroesContainerMdAndLgUdsHeroTextLineHeight",(function(){return $r})),t.d(o,"ComponentHeroesUdsHeroBackgroundSize",(function(){return Dr})),t.d(o,"ComponentHeroesUdsHeroBackgroundPosition",(function(){return Ir})),t.d(o,"ComponentHeroesUdsHeroWidthPercent",(function(){return Ur})),t.d(o,"ComponentHeroesUdsHeroHeight",(function(){return Wr})),t.d(o,"ComponentHeroesUdsHeroDisplay",(function(){return Ar})),t.d(o,"ComponentHeroesUdsHeroMaxWidth",(function(){return Rr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerWidthPx",(function(){return Gr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerDisplay",(function(){return Xr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerFlexDirection",(function(){return Nr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerAlignItems",(function(){return Er})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerMargin",(function(){return Yr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerH1MarginLeft",(function(){return _r})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerUdsHeroTextMarginLeft",(function(){return qr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerPColor",(function(){return Vr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerPFontSize",(function(){return Kr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroContainerPMarginBottom",(function(){return Jr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroSmHeight",(function(){return Qr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroSmContainerUdsHeroContainerWidthPercent",(function(){return Zr})),t.d(o,"ComponentHeroesUdsHeroUdsHeroMdHeight",(function(){return ni})),t.d(o,"ComponentHeroesUdsHeroUdsHeroLgHeight",(function(){return ei})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaBreakpoint",(function(){return ti})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaMarginBottom",(function(){return oi})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaH1MaxWidthPercent",(function(){return ri})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroContainerMediaPDisplay",(function(){return ii})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroSmBreakpoint",(function(){return ai})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroSmPaddingLeft",(function(){return di})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroSmPaddingBottom",(function(){return ui})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroLgBreakpoint",(function(){return ci})),t.d(o,"ComponentHeroesMediaUdsHeroUdsHeroLgHeight",(function(){return si})),t.d(o,"ComponentListSpacingPadding",(function(){return li})),t.d(o,"ComponentListSpacingListStyle",(function(){return fi})),t.d(o,"ComponentListSpacingLiMaxWidth",(function(){return mi})),t.d(o,"ComponentListSpacingLiMarginBottom",(function(){return pi})),t.d(o,"ComponentListSpacingLiLastOfTypeMarginBottom",(function(){return gi})),t.d(o,"ComponentListUlStylesContentBullet",(function(){return hi})),t.d(o,"ComponentListUlStylesContentBulletEmpty",(function(){return bi})),t.d(o,"ComponentListUlStylesFontSize",(function(){return Ci})),t.d(o,"ComponentListUlStylesVerticalAlign",(function(){return Bi})),t.d(o,"ComponentListUlStylesLineHeight",(function(){return yi})),t.d(o,"ComponentListUlStylesPaddingRight",(function(){return Oi})),t.d(o,"ComponentListUlStylesMarginLeft",(function(){return xi})),t.d(o,"ComponentListUlStylesSubListPadding",(function(){return Si})),t.d(o,"ComponentListMaroonListColor",(function(){return vi})),t.d(o,"ComponentListDarkmodeMarginLeft",(function(){return wi})),t.d(o,"ComponentListDarkmodeMarginBottom",(function(){return Li})),t.d(o,"ComponentListDarkmodeBackgroundColor",(function(){return Hi})),t.d(o,"ComponentListDarkmodeColor",(function(){return ji})),t.d(o,"ComponentListDarkmodeLiBeforeColor",(function(){return ki})),t.d(o,"ComponentListDarkmodeGoldColor",(function(){return Pi})),t.d(o,"ComponentListDarkmodeSteplistBackgroundColor",(function(){return Fi})),t.d(o,"ComponentListDarkmodeSteplistColor",(function(){return zi})),t.d(o,"ComponentListSmokemodeMarginLeft",(function(){return Ti})),t.d(o,"ComponentListSmokemodeMarginBottom",(function(){return Mi})),t.d(o,"ComponentListSmokemodeBackgroundColor",(function(){return $i})),t.d(o,"ComponentListIconListMarginLeft",(function(){return Di})),t.d(o,"ComponentListIconListMarginBottom",(function(){return Ii})),t.d(o,"ComponentListIconListPadding",(function(){return Ui})),t.d(o,"ComponentListIconListIconLeft",(function(){return Wi})),t.d(o,"ComponentListIconListLiBeforeContent",(function(){return Ai})),t.d(o,"ComponentListIconListLiBeforeFontSize",(function(){return Ri})),t.d(o,"ComponentListIconListLiBeforeVerticalAlign",(function(){return Gi})),t.d(o,"ComponentListIconListLiBeforeLineHeight",(function(){return Xi})),t.d(o,"ComponentListIconListLiBeforePaddingRight",(function(){return Ni})),t.d(o,"ComponentListIconListLiBeforeMarginLeft",(function(){return Ei})),t.d(o,"ComponentListIconListLiMaroonIcon",(function(){return Yi})),t.d(o,"ComponentListOlStylesNestedOlPadding",(function(){return _i})),t.d(o,"ComponentListOlStylesLiBeforeLineHeight",(function(){return qi})),t.d(o,"ComponentListOlStylesLiBeforePaddingRight",(function(){return Vi})),t.d(o,"ComponentListOlStylesLiBeforeMarginLeft",(function(){return Ki})),t.d(o,"ComponentListOlStylesLiNthOfType9MarginLeft",(function(){return Ji})),t.d(o,"ComponentListOlStylesLiNthOfType99MarginLeft",(function(){return Qi})),t.d(o,"ComponentListOlStylesSteplistStylesPaddingLeft",(function(){return Zi})),t.d(o,"ComponentListOlStylesSteplistStylesLiPaddingBottom",(function(){return na})),t.d(o,"ComponentListOlStylesSteplistStylesLiMarginBottom",(function(){return ea})),t.d(o,"ComponentListOlStylesSteplistStylesLiBorderBottom",(function(){return ta})),t.d(o,"ComponentListOlStylesSteplistStylesLiFontWeight",(function(){return oa})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanPaddingLeft",(function(){return ra})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanDisplay",(function(){return ia})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanMarginTop",(function(){return aa})),t.d(o,"ComponentListOlStylesSteplistStylesLiSpanFontWeight",(function(){return da})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeBorderRadius",(function(){return ua})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeBackgroundColor",(function(){return ca})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeColor",(function(){return sa})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforePadding",(function(){return la})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeMarginRight",(function(){return fa})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeMarginLeft",(function(){return ma})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeFontSize",(function(){return pa})),t.d(o,"ComponentListOlStylesSteplistStylesLiLiBeforeFontWeight",(function(){return ga})),t.d(o,"ComponentListOlStylesSteplistStylesGoldBackgroundColor",(function(){return ha})),t.d(o,"ComponentListOlStylesSteplistStylesGoldColor",(function(){return ba})),t.d(o,"ComponentListOlStylesSteplistStylesMaroonBackgroundColor",(function(){return Ca})),t.d(o,"ComponentPagerColor",(function(){return Ba})),t.d(o,"ComponentPagerBorderWidth",(function(){return ya})),t.d(o,"ComponentPagerBorderColor",(function(){return Oa})),t.d(o,"ComponentPagerBorder",(function(){return xa})),t.d(o,"ComponentPagerOutline",(function(){return Sa})),t.d(o,"ComponentPagerBackgroundColor",(function(){return va})),t.d(o,"ComponentPagerBorderRadius",(function(){return wa})),t.d(o,"ComponentPagerDisplay",(function(){return La})),t.d(o,"ComponentPagerFontWeight",(function(){return Ha})),t.d(o,"ComponentPagerTextDecoration",(function(){return ja})),t.d(o,"ComponentPagerLineHeight",(function(){return ka})),t.d(o,"ComponentPagerMaxWidth",(function(){return Pa})),t.d(o,"ComponentPagerHoverStateTransform",(function(){return Fa})),t.d(o,"ComponentPagerActiveStateTransform",(function(){return za})),t.d(o,"ComponentPagerPadding",(function(){return Ta})),t.d(o,"ComponentPagerHoverTextDecoration",(function(){return Ma})),t.d(o,"ComponentPagerHoverColor",(function(){return $a})),t.d(o,"ComponentPagerActiveBackgroundColor",(function(){return Da})),t.d(o,"ComponentPagerActiveColor",(function(){return Ia})),t.d(o,"ComponentPagerDisabledOpacity",(function(){return Ua})),t.d(o,"ComponentPagerIconHeight",(function(){return Wa})),t.d(o,"ComponentPagerIconWidth",(function(){return Aa})),t.d(o,"ComponentPagerIconMargin",(function(){return Ra}));var r=t(0);const i=(n,e,t)=>Object(r.i)(Object(r.h)(n,e),t),a=(n,e,t)=>Object(r.k)(Object(r.h)(n,e),t),d=()=>{let n={userName:"",loggedIn:!1};const e=document.cookie.split(";");for(let t=0;t<e.length;t++)if(e[t].indexOf("SSONAME")>0){if(""==e[t].substring(9))break;n.userName=e[t].substring(9),n.loggedIn=!0;break}return n},u=(n,e=!1,t="headerContainer")=>{const{loggedIn:o,userName:r,loginLink:u,...c}=n,s=u||(n=>{const e=window.location.toString();return n=(n=decodeURI(n)).replace("/login","/login?callapp="+e)})(pu.defaultProps.loginLink),l={...o&&r?{loggedIn:o,userName:r}:d(),...c,loginLink:s};e?i(pu,l,document.getElementById(t)):a(pu,l,document.getElementById(t))};var c=t(3),s=t(2),l=t(1),f=t.n(l);const m="FontAwesome",p="assets/fontawesome/webfonts/fa-regular-400.ttf",g="assets/fontawesome/webfonts/fa-regular-400.eot",h="assets/fontawesome/webfonts/fa-regular-400.woff",b="assets/fontawesome/webfonts/fa-regular-400.woff2",C="assets/fontawesome/sprites/regular.svg",B="0",y="576px",O="768px",x="992px",S="1260px",v="1400px",w="1920px",L="#cc2f2f",H="#ff7f32",j="#00a3e0",k="#78be20",P="#ffffff",F="#e8e8e8",z="#191919",T="#e9f5db",M="#f7dddd",$="#ffeade",D="#d6f0fa",I="#191919",U="#ffc627",W="#8c1d40",A="#ffffff",R="#78be20",G="#ff7f32",X="#00a3e0",N="#00baff",E="#7f6227",Y="#440e22",_="#fafafa",q="#e8e8e8",V="#d0d0d0",K="#bfbfbf",J="#747474",Q="#484848",Z="#191919",nn="#e8e8e8",en="#d0d0d0",tn="#bfbfbf",on="#00baff",rn="#cc2f2f",an="#ff7f32",dn="#78be20",un="#00a3e0",cn="#ffc627",sn="#8c1d40",ln="#191919",fn="#bfbfbf",mn="#191919",pn="#8c1d40",gn="#8c1d40",hn="#8c1d40",bn="#440e22",Cn="#b72a2a",Bn="#bd4800",yn="#446d12",On="#126877",xn="#fafafa",Sn="#ffc627",vn="#ffc627",wn="#ffc627",Ln="#7f6227",Hn="#ff7b7d",jn="#ff8034",kn="#78be20",Pn="#00b0f3",Fn="#1e1e1e",zn="#393939",Tn="Arial, Helvetica, 'Nimbus Sans L', 'Liberation Sans', FreeSans, sans-serif",Mn="FontAwesome",$n="100",Dn="300",In="400",Un="700",Wn="900",An="400",Rn="540px",Gn="768px",Xn="992px",Nn="1224px",En="12",Yn="24px",_n="34rem",qn="60rem",Vn="75rem",Kn="0.75rem",Jn="0.875rem",Qn="1rem",Zn="1.25rem",ne="1.5rem",ee="2rem",te="3rem",oe="1rem",re="1.5rem",ie="2rem",ae="2.5rem",de="3rem",ue="5rem",ce="0rem",se="0.5rem",le="1rem",fe="1.5rem",me="2rem",pe="2.5rem",ge="3rem",he="3.5rem",be="4rem",Ce="4.5rem",Be="5rem",ye="6rem",Oe="7rem",xe="8rem",Se="16rem",ve="32rem",we="0.25rem",Le="1rem",He="400",je="700",ke="200",Pe="400",Fe="600",ze="1000",Te="50",Me="100",$e="200",De="2000",Ie="4000",Ue="6000",We="0.875rem",Ae=".75rem",Re="1rem",Ge="0.5rem",Xe="1rem",Ne="transparent",Ee="#bfbfbf",Ye="#191919",_e="quote('/')",qe="none",Ve="30px",Ke="0rem",Je="0.5rem",Qe="0.5rem",Ze="padding-box",nt="0 0",et="no-repeat",tt="400rem",ot="block",rt="bold",it="none",at="1rem",dt="17.5rem",ut="scale(1.1)",ct="scale(1)",st="1rem 2rem",lt="1rem",ft="2rem",mt="0.5rem",pt="1rem",gt=".75rem",ht="0.25rem",bt="center",Ct=".03s ease-in-out",Bt="50%",yt="#bfbfbf",Ot="400rem",xt="normal",St="1.375rem",vt="2rem",wt="50%",Lt="2rem",Ht="100%",jt="#ffffff",kt="#bfbfbf",Pt="1rem",Ft="1rem",zt="#bfbfbf",Tt="25%",Mt="#191919",$t="#ffffff",Dt="50%",It="#bfbfbf",Ut="#ffffff",Wt="1rem",At="0.75rem",Rt="1.375rem",Gt="4rem",Xt="0.875rem",Nt="2rem",Et="5rem",Yt="2rem",_t="3rem",qt="8rem",Vt="#ffc627",Kt="#191919",Jt="#8c1d40",Qt="#fafafa",Zt="#191919",no="#fafafa",eo="#bfbfbf",to="#191919",oo="normal",ro="100%",io="flex",ao="column",uo="scale(1.05)",co="0px 8px 16px rgba(25,25,25,0.2)",so="pointer",lo="scale(1)",fo="100%",mo="12.5rem",po="10rem",go="15rem",ho="cover",bo="2rem",Co="2rem",Bo="2rem 2rem 0 2rem",yo="2rem auto 0 auto",Oo="2rem",xo="1.5rem",So="left",vo="center",wo="#191919",Lo="none",Ho="underline",jo="0 2rem 2rem 2rem",ko="0 1.5rem 1.5rem 1.5rem",Po="0 2rem 2rem 2rem",Fo="0 1.5rem 1.5rem 1.5rem",zo="100%",To="auto",Mo="flex-end",$o="flex-end",Do="1rem 2rem 1rem 2rem",Io="1rem 1rem 1rem 1rem",Uo="1px solid rgba(0, 0, 0, 0.125)",Wo="2rem",Ao="0.25rem",Ro="''",Go="block",Xo="#ffc627",No="1rem",Eo="0 2rem 0 2rem",Yo="0 1rem 0 1rem",_o="#ffffff",qo="60rem",Vo="1.5rem",Ko="Arial, Helvetica, 'Nimbus Sans L', 'Liberation Sans', FreeSans, sans-serif",Jo="700",Qo="left",Zo="1",nr="1rem",er="calc(100% + .12em)",tr="-0.15em",or="0",rr="0",ir="0.15em",ar="0",dr="0",ur="-0.15em",cr="0",sr="0",lr="0.15em",fr="0",mr="0",pr="#ffc627",gr="#191919",hr="#191919",br="#fafafa",Cr="#ffffff",Br="#191919",yr="4rem",Or="-0.035em",xr="3rem",Sr="2.25rem",vr="2.5rem",wr="-0.035em",Lr="2rem",Hr="-0.035em",jr="1.5rem",kr="-0.035em",Pr="1.25rem",Fr="-0.025em",zr="1rem",Tr="-0.015em",Mr="100%",$r="2rem",Dr="cover",Ir="top",Ur="100%",Wr="42.75rem",Ar="flex",Rr="1920px",Gr="800px",Xr="flex",Nr="column",Er="flex-start",Yr="auto auto 2rem auto",_r="0rem",qr="0rem",Vr="#ffffff",Kr="1.5rem",Jr="1.75rem",Qr="16rem",Zr="100%",ni="32rem",ei="42.75rem",ti="576px",oi="-2rem",ri="100%",ii="none",ai="576px",di="1.5rem",ui="2rem",ci="1400px",si="32rem",li="3rem 5rem 3rem 2rem",fi="none",mi="75rem",pi="1rem",gi="0rem",hi="\\2022 ",bi="\\25E6 ",Ci="2rem",Bi="middle",yi="1.5rem",Oi="1.25rem",xi="-2rem",Si="1rem 1.5rem 0rem",vi="#8c1d40",wi="0rem",Li="0rem",Hi="#191919",ji="#e8e8e8",ki="#e8e8e8",Pi="#ffc627",Fi="#e8e8e8",zi="#191919",Ti="0rem",Mi="0rem",$i="#e8e8e8",Di="0rem",Ii="0rem",Ui="3rem 5rem",Wi="-2.5rem",Ai="none",Ri="2rem",Gi="middle",Xi="1.5rem",Ni="1rem",Ei="-1.5rem",Yi="#8c1d40",_i="1rem 1.5rem 0rem",qi="1.5rem",Vi="1rem",Ki="-1.9rem",Ji="-2.4rem",Qi="-2.9rem",Zi="1.5rem",na="2rem",ea="3rem",ta="1px solid #bfbfbf",oa="bold",ra="0",ia="block",aa="1rem",da="normal",ua="50rem",ca="#191919",sa="#fafafa",la="0.5rem 0.8rem",fa="2rem",ma="-4.5rem",pa="1.25rem",ga="bold",ha="#ffc627",ba="#191919",Ca="#8c1d40",Ba="#191919",ya="0rem",Oa="#000000",xa="none",Sa="0",va="#000000",wa="400rem",La="block",Ha="bold",ja="none",ka="1rem",Pa="17.5rem",Fa="scale(1.1)",za="scale(1)",Ta="1rem 2rem",Ma="underline",$a="#ffffff",Da="#8c1d40",Ia="#ffffff",Ua="50%",Wa="1rem",Aa="1rem",Ra="0.25rem",Ga=s.a`
  position: absolute;
  width: 1px;
  height: 1px;
  margin: -1px;
  padding: 0;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  border: 0;
`;s.a`
  :not(:focus):not(:active) {
    clip: rect(0 0 0 0);
    clip-path: inset(100%);
    height: 1px;
    overflow: hidden;
    position: absolute;
    white-space: nowrap;
    width: 1px;
  }
`;var Xa=o;const Na=Object(c.b)((n,e)=>{const t="link"==n.type?"a":"button";return Object(r.h)(t,{class:Object(s.b)(s.a`
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
          transform: ${Xa.ComponentButtonHoverStateTransform};
        }

        :active {
          transform: ${Xa.ComponentButtonActiveStateTransform};
        }

        ${n.disabled&&s.a`
            opacity: ${Xa.ComponentButtonDisabledOpacity};
          `}

        ${n.small&&s.a`
            font-size: ${Xa.ComponentButtonSmallFontSize};
            height: ${Xa.ComponentButtonSmallHeight};
            min-width: ${Xa.ComponentButtonSmallMinWidth};
            padding: ${Xa.ComponentButtonPaddingYSmall}
              ${Xa.ComponentButtonPaddingXSmall};
          `}

        ${n.medium&&s.a`
            font-size: 0.875rem;
            padding: 0.5rem 1rem;
          `}

        ${n.large&&s.a`
            font-size: ${Xa.ComponentButtonLargeFontSize};
            height: ${Xa.ComponentButtonLargeHeight};
            min-width: ${Xa.ComponentButtonLargeMinWidth};
          `}

        ${n.gold&&s.a`
            color: ${Xa.ComponentButtonGoldColor};
            background-color: ${Xa.ComponentButtonGoldBackgroundColor};

            :hover {
              color: ${Xa.ComponentButtonGoldColor};
            }
          `}

        ${n.maroon&&s.a`
            color: #ffffff;
            background-color: #8c1d40;
            border-color: #8c1d40;

            :visited:not(.btn) {
              color: #ffffff;
            }
          `}

        ${n.dark&&s.a`
            color: ${Xa.ComponentButtonDarkColor};
            background-color: ${Xa.ComponentButtonDarkBackgroundColor};
          `}

        ${n.light&&s.a`
            color: ${Xa.ComponentButtonLightColor};
            background-color: ${Xa.ComponentButtonLightBackgroundColor};
          `}
      `,n.class),onClick:n.onClick,href:n.href,ref:e},n.children)});Na.propTypes={type:f.a.string,href:f.a.string,gold:f.a.bool,maroon:f.a.bool,disabled:f.a.bool,small:f.a.bool,medium:f.a.bool,large:f.a.bool,domRef:f.a.oneOfType([f.a.func,f.a.shape({current:f.a.instanceOf(f.a.element)})]),onFocus:f.a.func},Na.defaultProps={disabled:!1};const Ea=s.a`
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
      transform: ${Xa.ComponentButtonHoverStateTransform};
    }

    :active {
      transform: ${Xa.ComponentButtonActiveStateTransform};
    }

    &.btn-disabled {
      opacity: ${Xa.ComponentButtonDisabledOpacity};
    }

    &.btn-small {
      font-size: ${Xa.ComponentButtonSmallFontSize};
      height: ${Xa.ComponentButtonSmallHeight};
      min-width: ${Xa.ComponentButtonSmallMinWidth};
      padding: ${Xa.ComponentButtonPaddingYSmall}
        ${Xa.ComponentButtonPaddingXSmall};
    }

    &.btn-medium {
      font-size: ${Xa.ComponentButtonMediumFontSize};
      height: ${Xa.ComponentButtonMediumHeight};
      min-width: ${Xa.ComponentButtonMediumMinWidth};
      padding: ${Xa.ComponentButtonPaddingYMedium}
        ${Xa.ComponentButtonPaddingXMedium};
    }

    &.btn-large {
      font-size: ${Xa.ComponentButtonLargeFontSize};
      height: ${Xa.ComponentButtonLargeHeight};
      min-width: ${Xa.ComponentButtonLargeMinWidth};
    }

    &.btn-gold {
      color: ${Xa.ComponentButtonGoldColor};
      background-color: ${Xa.ComponentButtonGoldBackgroundColor};
    }

    &.btn-maroon {
      color: ${Xa.ComponentButtonMaroonColor};
      background-color: ${Xa.ComponentButtonMaroonBackgroundColor};
    }

    &.btn-dark {
      color: ${Xa.ComponentButtonDarkColor};
      background-color: ${Xa.ComponentButtonDarkBackgroundColor};
    }

    &.btn-light {
      color: ${Xa.ComponentButtonLightColor};
      background-color: ${Xa.ComponentButtonLightBackgroundColor};
    }
  }
`;function Ya(){return(Ya=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const _a=Object(c.b)(({href:n,children:e,...t},o)=>{const i=n?"link":"button";return Object(r.h)(Na,Ya({type:i,ref:o},n?{href:n}:{},t),e)});_a.propTypes={type:f.a.string,href:f.a.string,gold:f.a.bool,maroon:f.a.bool,disabled:f.a.bool,small:f.a.bool,medium:f.a.bool,large:f.a.bool,itemRef:f.a.oneOfType([f.a.func,f.a.shape({current:f.a.instanceOf(f.a.element)})]),onFocus:f.a.func},_a.defaultProps={disabled:!1};var qa=t(4),Va=t(5);function Ka(){return(Ka=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Ja=n=>Object(r.h)(qa.a,Ka({icon:Va.a},n)),Qa=n=>Object(r.h)(qa.a,Ka({icon:Va.l},n)),Za=n=>Object(r.h)(qa.a,Ka({icon:Va.c},n)),nd=n=>Object(r.h)(qa.a,Ka({icon:Va.k},n)),ed=n=>Object(r.h)(qa.a,Ka({icon:Va.f},n)),td=n=>Object(r.h)(qa.a,Ka({icon:Va.e},n)),od=n=>Object(r.h)(qa.a,Ka({icon:Va.j},n)),rd=n=>Object(r.h)(qa.a,Ka({icon:Va.g},n)),id=n=>Object(r.h)(qa.a,Ka({icon:Va.b},n)),ad=n=>Object(r.h)(qa.a,Ka({icon:Va.i},n)),dd=n=>Object(r.h)("span",{class:Object(s.b)("fa-layers fa-fw",n.class)},Object(r.h)(qa.a,{icon:Va.d,size:"2x"}),Object(r.h)(qa.a,{icon:Va.m,size:"1x"})),ud=n=>Object(r.h)(qa.a,Ka({icon:Va.h},n)),cd=({type:n,...e})=>{switch(n){case"mobile":return Object(r.h)(nd,null);case"chevron-down":return Object(r.h)(Za,e);case"search":return Object(r.h)(Qa,e);case"desktop":return Object(r.h)(ed,e);case"clipboard":return Object(r.h)(td,e);case"map-pin":return Object(r.h)(od,e);case"exclamation-triangle":return Object(r.h)(rd,e);case"bell":return Object(r.h)(id,e);case"info-circle":return Object(r.h)(ad,e);case"circle-close":return Object(r.h)(dd,e);case"bars":return Object(r.h)(Ja,e);case"home":return Object(r.h)(ud,e);default:return""}};function sd(){return(sd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}cd.propTypes={type:f.a.string.isRequired},cd.defaultProps={};const ld=({show:n,id:e,...t})=>Object(r.h)("div",sd({},e?{id:e}:{},{class:Object(s.b)(s.a`
          padding: 0 32px 24px 32px;
          flex-grow: 100;
          flex: 1 1 auto;
          min-height: 1px;
          padding: 1.25rem;
          ${!n&&s.a`
            display: none;
          `}
        `,t.class),dangerouslySetInnerHTML:{__html:t.children}})),fd=n=>Object(r.h)("div",{class:Object(s.b)(s.a`
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
        `,n.class)},n.children),md=({show:n,id:e,...t})=>Object(r.h)(ld,sd({},e?{id:e}:{},{show:n,class:Object(s.b)(s.a`
          ${n&&s.a`
            border-top: 1px solid #d0d0d0;
          `}
        `,t.class)}),t.children),pd=({show:n,id:e,...t})=>Object(r.h)("button",sd({"aria-expanded":n},e?{"aria-controls":e}:{},{role:"button",class:s.a`
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

        ${n?s.a`
                .fa-chevron-down {
                  transform: rotate(-180deg);
                }
              `:""}

      `},t),t.children,Object(r.h)(cd,{type:"chevron-down"})),gd=({head:n,children:e,id:t,...o})=>{const[i,a]=Object(c.f)(!1);return Object(r.h)(fd,{class:o.class},Object(r.h)(pd,{show:i,id:t,onClick:n=>{a(n=>!n)}},n),Object(r.h)(md,{show:i,id:t},e))};function hd(){return(hd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}gd.propTypes={head:f.a.node,children:f.a.node,class:f.a.string,id:f.a.string},gd.defaultProps={};const bd=s.a`
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
`,Cd=n=>Object(r.h)("form",{class:"navbar-site-buttons"},n.children),Bd=s.a`
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
`,yd=n=>Object(r.h)("div",{class:Object(s.b)("dropdown",n.open?"open":"")},n.children),Od=s.a`
  .nav-icon {
    color: #191919;
  }
`,xd=s.a`

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
    ${Ga}
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
      ${(n=>{const e=n||"relative";return s.a`
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
      ${Ga}
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

  ${Bd}
  ${bd}
  ${Od};
`,Sd=s.a`
  nav.header-nav {
    ${xd}
  }
`,vd=({open:n,maxMobileHeight:e,injectStyles:t,children:o,...i})=>{const a=-1==e?"75vh":e+"px";return Object(r.h)("nav",hd({id:"asu-header-nav",class:Object(s.b)("header-nav",n?"open-nav":"",s.a`
          @media (max-width: ${"992px"}) {
            &.open-nav,
            &:target {
              flex-direction: column;
              width: 100%;

              max-height: ${a};
              display: flex;
            }
          }
        `,t?xd:"")},i),o)};function wd(){return(wd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Ld=s.a`
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
`,Hd=n=>Object(r.h)("div",wd({class:Object(s.b)("asu-search-form",n.class)},n),n.children),jd=s.a`
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
`,kd=n=>Object(r.h)("div",{class:Object(s.b)(n.class,"login-status")},n.children);function Pd(){return(Pd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Fd=({children:n,...e})=>Object(r.h)("header",Pd({},e,{class:Object(s.b)(e.class,s.a`
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
        `,Dd,Sd,Ea,Ud,Ad,Md,Ld,Gd,jd,zd)}),n),zd=s.a`
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
`,Td=({mobileOpen:n,...e})=>Object(r.h)("button",Pd({},e,{class:Object(s.b)(s.a`
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
        `,"navbar-toggler")}),n?Object(r.h)(cd,{type:"circle-close"}):Object(r.h)(cd,{type:"bars",href:"#asu-header-nav"})),Md=s.a`
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
`,$d=n=>Object(r.h)("div",{class:Object(s.b)("universal-nav",n.open?"mobile-open":"",n.searchOpen?"search-open":""),ref:n.domRef},n.children),Dd=s.a`
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
`,Id=n=>Object(r.h)("div",{class:"primary-nav"},n.children),Ud=s.a`
  .navbar-container {
    display: flex;
    width: 100%;
    flex-direction: column;
    align-items: flex-start;

    @media (max-width: ${"992px"}) {
      width: 100%;
    }
  }
`,Wd=n=>Object(r.h)("div",{class:Object(s.b)("navbar-container",n.class)},n.children),Ad=s.a`
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
`,Rd=n=>{const e=n.brandLink?n.brandLink:"https://asu.edu";return Object(r.h)("a",{href:e,class:"navbar-brand",ref:n.domRef},Object(r.h)("img",{class:"vert",src:n.src,alt:n.alt}),Object(r.h)("img",{class:"horiz",src:n.mobileSrc}))},Gd=s.a`
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
`,Xd=Object(c.b)(({title:n,unit:e,...t},o)=>e?Object(r.h)("div",{class:"title",ref:o},Object(r.h)("a",{class:"unit-name"},e),Object(r.h)("span",{class:"subdomain-name"},n)):Object(r.h)("div",{class:"title subdomain-name",ref:o},n));function Nd(){return(Nd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const Ed=s.a`
  font-weight: 700;
  text-align: left;
  opacity: 1;
  margin: 1rem 0;
  line-height: calc(100% + 0.12em);
`,Yd=({children:n,...e})=>Object(r.h)("h4",Nd({},e,{class:Object(s.b)(s.a`
          ${Ed}
          font-size: 1.25rem;
          letter-spacing: -0.025em;
        `,e.class)}),n),_d=({children:n,...e})=>Object(r.h)("h3",Nd({},e,{class:Object(s.b)(s.a`
          ${Ed}
          font-size: 1.5rem;
          letter-spacing: -0.035em;
        `,e.class)}),n),qd=({type:n,...e})=>{switch(n){case"h4":return Object(r.h)(Yd,{class:e.class},e.children);case"h3":return Object(r.h)(_d,{class:e.class},e.children);default:return""}};function Vd(){return(Vd=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}qd.propTypes={type:f.a.string.isRequired},qd.defaultProps={};const Kd=({onFocus:n,itemRef:e,type:t,text:o,color:i,href:a,...d})=>{let u="";switch(t){case"button":u=Object(r.h)(_a,Vd({class:"nav-button",ref:e,href:a},n?{onFocus:n}:"",{medium:!0,dark:!0}),o);break;case"icon":u=Object(r.h)("a",Vd({class:"nav-icon",href:a},n?{onFocus:n}:"",{ref:e}),Object(r.h)(cd,{type:d.class,className:"icon-nav-item"}),Object(r.h)("span",{class:"mobile-only"},o));break;case"heading":return Object(r.h)(qd,{type:"h3"},o);default:u=Object(r.h)("a",Vd({class:"nav-item",href:a},n?{onFocus:n}:"",{ref:e}),o)}return Object(r.h)("li",null,u)};Kd.propTypes={itemRef:f.a.oneOfType([f.a.func,f.a.shape({current:f.a.instanceOf(f.a.element)})]),location:f.a.array,onFocus:f.a.func,type:f.a.string,href:f.a.string,text:f.a.string.isRequired,color:f.a.string,icon:f.a.string},Kd.defaultProps={};var Jd=Kd;const Qd=({item:n,submenus:e,mobileWidth:t,width:o,setFocus:i,pIndex:a,isOpen:d,setOpen:u,topRef:c,hasFocus:s,...l})=>{const f=n=>{u(d?-1:n)};return Object(r.h)("li",null,Object(r.h)("a",{target:n.target,title:n.title?n.title:n.text,role:"button","aria-expanded":d,onMouseDown:n=>{n.preventDefault(),f(a)},onKeyDown:n=>{const e=n.keyCode;32!=e&&13!=e||f(a)},onFocus:n=>{i([a,-1,-1])},tabIndex:"0",ref:c},n.text," ",Object(r.h)(Za,{sr:n.text,className:d?"open":""})),Object(r.h)(yd,{open:d},e.map((n,t)=>Object(r.h)("ul",null,n.map((n,o)=>Object(r.h)(Jd,{onFocus:()=>{i([a,t,o]),(n=>{u(n)})(a)},itemRef:e[t][o].ref,type:n.hasOwnProperty("type")?n.type:void 0,color:n.hasOwnProperty("color")?n.color:void 0,class:n.hasOwnProperty("class")?n.class:void 0,href:n.hasOwnProperty("href")?n.href:void 0,text:n.text}))))))};Qd.propTypes={setFocus:f.a.func,location:f.a.array,item:f.a.object.isRequired,submenus:f.a.arrayOf(f.a.arrayOf(f.a.object)).isRequired,topRef:f.a.oneOfType([f.a.func,f.a.shape({current:f.a.instanceOf(f.a.element)})]),mobileWidth:f.a.number,width:f.a.number,pIndex:f.a.number.isRequired,isOpen:f.a.bool,setOpen:f.a.func,hasFocus:f.a.bool},Qd.defaultProps={menus:[],top:!1,mobileWidth:992,isOpen:!1};var Zd=Qd;function nu(){return(nu=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const eu=({navTree:n,width:e,height:t,mobileOpen:o,maxMobileHeight:i,buttons:a,injectStyles:d,...u})=>{const[s,l]=Object(c.f)([-1,-1,-1]),[f,m]=Object(c.f)(-1),p=n=>{l(n)},g=parseInt("992px",10),h=Object(c.d)(()=>n.map(n=>{const e=Object(r.g)();let t=[],{items:o,...i}=n;if(o&&o[0].length>0)for(let n=0;n<o.length;n++)for(let e=0;e<o[n].length;e++)if(t[n]||(t[n]=[]),t[n][e]=Object.assign({},o[n][e]),"heading"!=o[n][e].type){const o=Object(r.g)();t[n][e].ref=o}return{ref:e,item:i,menus:t}}),[n]);Object(c.c)(()=>{const n=tu(s,h);if(n.hasFocus){const[e,t,o]=s;n.isTop?h[e].ref&&h[e].ref.current.focus():h[e].menus[t][o].ref&&h[e].menus[t][o].ref.current.focus()}},[s,h]);const b=Object(c.e)(null);Object(c.c)(()=>{const n=n=>{b.current&&!b.current.contains(n.target)&&m(-1)};return document.addEventListener("mousedown",n),()=>{document.removeEventListener("mousedown",n)}},[b]);return Object(r.h)(vd,{open:o,maxMobileHeight:i,injectStyles:d},Object(r.h)("ul",nu({},e>g?{onfocusout:n=>{n.currentTarget.contains(n.relatedTarget)||p([-1,-1,-1])}}:{},{"aria-label":"ASU",onKeyDown:n=>{const e=tu(s,h);if(e.hasFocus)switch(n.keyCode){case 37:n.preventDefault(),p(ou(s,e,h));break;case 39:n.preventDefault(),p(ru(s,e,h));break;case 38:n.preventDefault(),p(iu(s,e,h));break;case 40:n.preventDefault(),p(au(s,e,h));break;case 9:if(n.shiftKey){if(e.isFirst)return!1;n.preventDefault(),p(ou(s,e,h))}else{if(e.isLast)return!1;n.preventDefault(),p(ru(s,e,h))}}},ref:b}),h.map((n,t)=>{const o=n.item,i=n.menus;let a=!1;return f==t&&(a=!0),i&&i.length>0&&i[0].length>0?Object(r.h)(Zd,{width:e,item:o,submenus:i,pIndex:t,setFocus:p,topRef:n.ref,isOpen:a,setOpen:m,mobileWidth:g}):Object(r.h)(Jd,{onFocus:()=>{p([t,-1,-1])},itemRef:n.ref,type:o.hasOwnProperty("type")?o.type:void 0,color:o.hasOwnProperty("color")?o.color:void 0,class:o.hasOwnProperty("class")?o.class:"",href:o.hasOwnProperty("href")?o.href:void 0,text:o.text})})),a.length>0&&Object(r.h)(Cd,null,a.map((n,e)=>{let t=n.color?n.color:"maroon";return Object(r.h)(_a,nu({href:n.href},{[t]:!0},{medium:!0}),n.text)})))};eu.propTypes={navTree:f.a.arrayOf(f.a.object),buttons:f.a.arrayOf(f.a.object),mobileOpen:f.a.bool,width:f.a.number,height:f.a.number,maxMobileHeight:f.a.number,injectStyles:f.a.bool},eu.defaultProps={navTree:[],mobileOpen:!1,width:1920,height:1080,maxMobileHeight:-1,buttons:[],injectStyles:!1};const tu=(n,e)=>{const[t,o,r]=n;let i=!1,a=!1,d=!1,u=!1,c=!1;return-1==t&&-1==o&&-1==r?{hasFocus:i}:(i=!0,e[t].menus.length>0&&(d=!0),a=-1===o||-1===r,a&&t===e.length-1&&(u=!0),a&&0===t&&(c=!0),{hasFocus:i,isTop:a,hasSubs:d,isLast:u,isFirst:c})},ou=(n,e,t)=>{const[o,r,i]=n;let a=n;return e.isTop?(a=void 0!==t[o-1]?[o-1,-1,-1]:[0,-1,-1],!1===du(a,t)?ou(a,tu(a,t),t):a):void 0!==t[o].menus[r-1]?t[o].menus[r-1][0].ref?[o,r-1,0]:[o,r-1,1]:[o,-1,-1]},ru=(n,e,t)=>{const[o,r,i]=n;let a=n;return e.isTop?(a=void 0!==t[o+1]?[o+1,-1,-1]:[t.length-1,-1,-1],!1===du(a,t)?ru(a,tu(a,t),t):a):void 0!==t[o].menus[r+1]?t[o].menus[r+1][0].ref?[o,r+1,0]:[o,r+1,1]:[o,-1,-1]},iu=(n,e,t)=>{const[o,r,i]=n;let a=[],d=n;return e.hasSubs&&(a=t[o].menus),d=e.isTop?ou(n,e,t):void 0!==a[r][i-1]?[o,r,i-1]:[o,-1,-1],!1===du(d,t)?iu(d,tu(d,t),t):d},au=(n,e,t)=>{const[o,r,i]=n;let a=[],d=n;return e.hasSubs&&(a=t[o].menus),d=e.isTop&&e.hasSubs?[o,0,0]:e.isTop?ru(n,e,t):void 0!==a[r][i+1]?[o,r,i+1]:ru(n,e,t),!1===du(d,t)?au(d,tu(d,t),t):d},du=(n,e)=>{const t=tu(n,e);if(!t.hasFocus)return!1;if(t.isTop){if(e[n[0]].ref)return!0}else if(e[n[0]].menus[n[1]][n[2]].ref)return!0;return!1};function uu(){return(uu=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}const cu=({type:n,open:e,inputRef:t,mobile:o,...i})=>{switch(n){case"d7":return Object(r.h)("div",null,"Drupal 7");default:return Object(r.h)("form",{action:"https://search.asu.edu/search",method:"get",role:"search",class:e?"show-search-input":""},Object(r.h)("input",uu({name:"q",type:"search"},t?{ref:t}:{},{"aria-labelledby":"asu-search-label"},o?{placeHolder:"Search ASU"}:{},{required:!0})),Object(r.h)("label",{class:"univeral-search",id:"asu-search-label"},"Search ASU"))}};cu.propTypes={type:f.a.string,open:f.a.bool,inputRef:f.a.oneOfType([f.a.func,f.a.shape({current:f.a.instanceOf(f.a.element)})]),mobile:f.a.bool},cu.defaultProps={};const su=({type:n,open:e,setOpen:t,mobile:o})=>{const i=Object(c.e)(null);return Object(r.h)(Hd,{onfocusin:()=>t(!0),onfocusout:n=>{i.current.value||n.currentTarget.contains(n.relatedTarget)||t(!1)},onClick:n=>{t(!0),i.current.focus()}},Object(r.h)(cu,{open:e,type:n,inputRef:i,mobile:o}))};su.propTypes={type:f.a.string,open:f.a.bool,setOpen:f.a.func,mobile:f.a.bool},su.defaultProps={open:!1};const lu=({loggedIn:n,loginLink:e,logoutLink:t,userName:o,...i})=>Object(r.h)(kd,{class:i.class},n?Object(r.h)(r.b,null,o?Object(r.h)("span",{class:"name"},o):"",Object(r.h)("a",{class:"signout",href:t},"Sign Out")):Object(r.h)("a",{href:e},"Sign in"));function fu(){const n="undefined"!=typeof window,{innerWidth:e,innerHeight:t}=n?window:{innerWidth:1920,innerHeight:1080};return{width:e,height:t}}function mu(){return(mu=Object.assign||function(n){for(var e=1;e<arguments.length;e++){var t=arguments[e];for(var o in t)Object.prototype.hasOwnProperty.call(t,o)&&(n[o]=t[o])}return n}).apply(this,arguments)}lu.propTypes={class:f.a.string,loggedIn:f.a.bool.isRequired,loginLink:f.a.string,logoutLink:f.a.string,userName:f.a.string},lu.defaultProps={logoutLink:"https://webapp4.asu.edu/myasu/Signout",loginLink:"https://weblogin.asu.edu/cgi-bin/login",loggedIn:!1};const pu=({navTree:n,title:e,unit:t,logo:o,loggedIn:i,userName:a,loginLink:d,logoutLink:u,buttons:s,...l})=>{const[f,m]=Object(c.f)(!1),[p,g]=Object(c.f)(!1),[h,b]=Object(c.f)(-1),C=parseInt("992px",10),{height:B,width:y}=function(){const[n,e]=Object(c.f)(fu());return Object(c.c)(()=>{function n(){e(fu())}return window.addEventListener("resize",n),()=>window.removeEventListener("resize",n)},[]),n}(),[O,x]=Object(c.f)(0),S=()=>{const n=window.pageYOffset;x(n)};Object(c.c)(()=>(window.addEventListener("scroll",S,{passive:!0}),()=>{window.removeEventListener("scroll",S)}),[]);const v=parseInt("24px",10),w=Object(c.e)(null),L=Object(c.e)(null),H=Object(c.e)(null);return Object(c.c)(()=>{y<C&&f&&window.setTimeout(()=>{const n=w.current.clientHeight,e=L.current.clientHeight,t=H.current.clientHeight;b(B-n-(e+t+v))},500)},[B,y,f]),Object(r.h)(Fd,{class:O>0||f&&y<C?"scrolled":""},Object(r.h)($d,mu({open:f,domRef:w},{searchOpen:p}),Object(r.h)("div",null,Object(r.h)("div",{class:"nav-grid"},Object(r.h)("a",{href:"https://www.asu.edu/"},"ASU home"),Object(r.h)("a",{href:"https://my.asu.edu/"},"My ASU"),Object(r.h)("a",{href:"https://www.asu.edu/colleges/"},"Colleges and schools"),Object(r.h)(lu,{loggedIn:i,loginLink:d,logoutLink:u,userName:a})),Object(r.h)(su,{open:p,setOpen:g,mobile:y<C}))),Object(r.h)(Id,null,l.dangerouslyGenerateStub?Object(r.h)("div",{id:"asu-generated-stub"}):Object(r.h)("div",null,Object(r.h)(Rd,mu({},o,{domRef:L})),Object(r.h)(Td,{onClick:n=>{n.preventDefault(),m(n=>!n)},mobileOpen:f}),Object(r.h)(Wd,null,Object(r.h)(Xd,mu({title:e,unit:t},{ref:H})),Object(r.h)(eu,{navTree:n,logo:o,mobileOpen:f,height:B,width:y,buttons:s,maxMobileHeight:h})))))};pu.propTypes={navTree:f.a.arrayOf(f.a.object),logo:f.a.shape({alt:f.a.string,src:f.a.string,mobileSrc:f.a.string,brandLink:f.a.string}),title:f.a.string,unit:f.a.string,loggedIn:f.a.bool,userName:f.a.string,loginLink:f.a.string,logoutLink:f.a.string,buttons:f.a.arrayOf(f.a.object)},pu.defaultProps={navTree:[],dangerouslyGenerateStub:!1,logo:{alt:"Arizona State University Logo",src:"https://i.imgur.com/5WtkgkV.png",mobileSrc:"https://www.asu.edu/asuthemes/4.10/assets/arizona-state-university-logo.png"},title:"",unit:"",loggedIn:lu.defaultProps.loggedIn,loginLink:lu.defaultProps.loginLink,logoutLink:lu.defaultProps.logoutLink,buttons:[]};const gu=n=>Object(r.h)("div",{class:Object(s.b)(n.class,s.a`
          padding: 2rem;
          margin-bottom: 2rem;
          border-radius: 0.3rem;
          border: 1px solid #dee2e6;
        `)},n.children),hu=n=>Object(r.h)(gu,{class:n.class},n.children);hu.propTypes={class:f.a.string},hu.defaultProps={}}})}));