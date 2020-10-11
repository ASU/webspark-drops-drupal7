!function(e,t){"object"==typeof exports&&"object"==typeof module?module.exports=t():"function"==typeof define&&define.amd?define("AsuWebcore",[],t):"object"==typeof exports?exports.AsuWebcore=t():e.AsuWebcore=t()}(window,(function(){return function(e){function t(t){for(var r,a,s=t[0],c=t[1],l=t[2],p=0,h=[];p<s.length;p++)a=s[p],Object.prototype.hasOwnProperty.call(i,a)&&i[a]&&h.push(i[a][0]),i[a]=0;for(r in c)Object.prototype.hasOwnProperty.call(c,r)&&(e[r]=c[r]);for(d&&d(t);h.length;)h.shift()();return o.push.apply(o,l||[]),n()}function n(){for(var e,t=0;t<o.length;t++){for(var n=o[t],r=!0,s=1;s<n.length;s++){var c=n[s];0!==i[c]&&(r=!1)}r&&(o.splice(t--,1),e=a(a.s=n[0]))}return e}var r={},i={0:0},o=[];function a(t){if(r[t])return r[t].exports;var n=r[t]={i:t,l:!1,exports:{}};return e[t].call(n.exports,n,n.exports,a),n.l=!0,n.exports}a.m=e,a.c=r,a.d=function(e,t,n){a.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:n})},a.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},a.t=function(e,t){if(1&t&&(e=a(e)),8&t)return e;if(4&t&&"object"==typeof e&&e&&e.__esModule)return e;var n=Object.create(null);if(a.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var r in e)a.d(n,r,function(t){return e[t]}.bind(null,r));return n},a.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return a.d(t,"a",t),t},a.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},a.p="";var s=window.webpackJsonpAsuWeb_name_=window.webpackJsonpAsuWeb_name_||[],c=s.push.bind(s);s.push=t,s=s.slice();for(var l=0;l<s.length;l++)t(s[l]);var d=c;return o.push([13,1]),n()}({13:function(e,t,n){"use strict";n.r(t),n.d(t,"Button",(function(){return g})),n.d(t,"FoldableCard",(function(){return N})),n.d(t,"Header",(function(){return Ue})),n.d(t,"Heading",(function(){return ve})),n.d(t,"Icon",(function(){return R})),n.d(t,"Nav",(function(){return Fe})),n.d(t,"Panel",(function(){return Be})),n.d(t,"HydratePreact",(function(){return i})),n.d(t,"RenderPreact",(function(){return o})),n.d(t,"initHeader",(function(){return s})),n.d(t,"checkSSOCookie",(function(){return a}));var r=n(0);const i=(e,t,n)=>Object(r.i)(Object(r.h)(e,t),n),o=(e,t,n)=>Object(r.k)(Object(r.h)(e,t),n),a=()=>{let e={userName:"",loggedIn:!1};const t=document.cookie.split(";");for(let n=0;n<t.length;n++)if(t[n].indexOf("SSONAME")>0){if(""==t[n].substring(9))break;e.userName=t[n].substring(9),e.loggedIn=!0;break}return e},s=(e,t=!1,n="headerContainer")=>{const{loggedIn:r,userName:s,loginLink:c,...l}=e,d=c||(e=>{const t=window.location.toString();return e=(e=decodeURI(e)).replace("/login","/login?callapp="+t)})(Ue.defaultProps.loginLink),p={...r&&s?{loggedIn:r,userName:s}:a(),...l,loginLink:d};t?i(Ue,p,document.getElementById(n)):o(Ue,p,document.getElementById(n))};var c=n(3),l=n(2),d=n(1),p=n.n(d);const h=l.a`
  position: absolute;
  width: 1px;
  height: 1px;
  margin: -1px;
  padding: 0;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  border: 0;
`;l.a`
  :not(:focus):not(:active) {
    clip: rect(0 0 0 0);
    clip-path: inset(100%);
    height: 1px;
    overflow: hidden;
    position: absolute;
    white-space: nowrap;
    width: 1px;
  }
`;function b(){return(b=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const u=Object(c.c)(({disabled:e,small:t,medium:n,large:i,gold:o,maroon:a,dark:s,light:c,type:d,...p},h)=>{const u="link"==d?"a":"button";return Object(r.h)(u,b({},p,{class:Object(l.b)(l.a`
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
              transform: ${"scale(1.1)"};
            }

            :active {
              transform: ${"scale(1)"};
            }

            ${e&&l.a`
              opacity: ${"50%"};
            `}

            ${t&&l.a`
              font-size: ${"0.75rem"};
              height: ${"1.375rem"};
              min-width: ${"4rem"};
              padding: ${"0.25rem"}
                ${".75rem"};
            `}

        ${n&&l.a`
              font-size: 0.875rem;
              padding: 0.5rem 1rem;
            `}

        ${i&&l.a`
              font-size: ${"2rem"};
              height: ${"3rem"};
              min-width: ${"8rem"};
            `}

        ${o&&l.a`
              color: ${"#191919"};
              background-color: ${"#ffc627"};

              :hover {
                color: ${"#191919"};
              }
            `}

        ${a&&l.a`
              color: #ffffff;
              background-color: #8c1d40;
              border-color: #8c1d40;

              :visited:not(.btn) {
                color: #ffffff;
              }
            `}

        ${s&&l.a`
              color: ${"#fafafa"};
              background-color: ${"#191919"};
            `}

        ${c&&l.a`
              color: ${"#191919"};
              background-color: ${"#bfbfbf"};
            `}
          `,p.class),ref:h}),p.children)});u.propTypes={type:p.a.string,href:p.a.string,gold:p.a.bool,maroon:p.a.bool,disabled:p.a.bool,small:p.a.bool,medium:p.a.bool,large:p.a.bool,onFocus:p.a.func},u.defaultProps={disabled:!1};const f=l.a`
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
      transform: ${"scale(1.1)"};
    }

    :active {
      transform: ${"scale(1)"};
    }

    &.btn-disabled {
      opacity: ${"50%"};
    }

    &.btn-small {
      font-size: ${"0.75rem"};
      height: ${"1.375rem"};
      min-width: ${"4rem"};
      padding: ${"0.25rem"} ${".75rem"};
    }

    &.btn-medium {
      font-size: ${"0.875rem"};
      height: ${"2rem"};
      min-width: ${"5rem"};
      padding: ${"0.5rem"} ${"1rem"};
    }

    &.btn-large {
      font-size: ${"2rem"};
      height: ${"3rem"};
      min-width: ${"8rem"};
    }

    &.btn-gold {
      color: ${"#191919"};
      background-color: ${"#ffc627"};
    }

    &.btn-maroon {
      color: ${"#fafafa"};
      background-color: ${"#8c1d40"};
    }

    &.btn-dark {
      color: ${"#fafafa"};
      background-color: ${"#191919"};
    }

    &.btn-light {
      color: ${"#191919"};
      background-color: ${"#bfbfbf"};
    }
  }
`;function m(){return(m=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const g=Object(c.c)(({href:e,children:t,...n},i)=>{const o=e?"link":"button";return Object(r.h)(u,m({type:o,ref:i},e?{href:e}:{},n),t)});g.propTypes={type:p.a.string,href:p.a.string,gold:p.a.bool,maroon:p.a.bool,disabled:p.a.bool,small:p.a.bool,medium:p.a.bool,large:p.a.bool,itemRef:p.a.oneOfType([p.a.func,p.a.shape({current:p.a.instanceOf(p.a.element)})]),onFocus:p.a.func},g.defaultProps={disabled:!1};var O=n(4),y=n(5);function v(){return(v=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const j=e=>Object(r.h)(O.a,v({icon:y.a},e)),w=e=>Object(r.h)(O.a,v({icon:y.l},e)),x=e=>Object(r.h)(O.a,v({icon:y.c},e)),k=e=>Object(r.h)(O.a,v({icon:y.k},e)),$=e=>Object(r.h)(O.a,v({icon:y.f},e)),z=e=>Object(r.h)(O.a,v({icon:y.e},e)),P=e=>Object(r.h)(O.a,v({icon:y.j},e)),S=e=>Object(r.h)(O.a,v({icon:y.g},e)),T=e=>Object(r.h)(O.a,v({icon:y.b},e)),L=e=>Object(r.h)(O.a,v({icon:y.i},e)),F=e=>Object(r.h)("span",{class:Object(l.b)("fa-layers fa-fw",e.class)},Object(r.h)(O.a,{icon:y.d,size:"2x"}),Object(r.h)(O.a,{icon:y.m,size:"1x"})),I=e=>Object(r.h)(O.a,v({icon:y.h},e)),R=({type:e,...t})=>{switch(e){case"mobile":return Object(r.h)(k,null);case"chevron-down":return Object(r.h)(x,t);case"search":return Object(r.h)(w,t);case"desktop":return Object(r.h)($,t);case"clipboard":return Object(r.h)(z,t);case"map-pin":return Object(r.h)(P,t);case"exclamation-triangle":return Object(r.h)(S,t);case"bell":return Object(r.h)(T,t);case"info-circle":return Object(r.h)(L,t);case"circle-close":return Object(r.h)(F,t);case"bars":return Object(r.h)(j,t);case"home":return Object(r.h)(I,t);default:return""}};function H(){return(H=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}R.propTypes={type:p.a.string.isRequired},R.defaultProps={};const M=({show:e,id:t,...n})=>Object(r.h)("div",H({},t?{id:t}:{},{class:Object(l.b)(l.a`
          padding: 0 32px 24px 32px;
          flex-grow: 100;
          flex: 1 1 auto;
          min-height: 1px;
          padding: 1.25rem;
          ${!e&&l.a`
            display: none;
          `}
        `,n.class),dangerouslySetInnerHTML:{__html:n.children}})),D=e=>Object(r.h)("div",{class:Object(l.b)(l.a`
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
        `,e.class)},e.children),C=({show:e,id:t,...n})=>Object(r.h)(M,H({},t?{id:t}:{},{show:e,class:Object(l.b)(l.a`
          ${e&&l.a`
            border-top: 1px solid #d0d0d0;
          `}
        `,n.class)}),n.children),A=({show:e,id:t,...n})=>Object(r.h)("button",H({"aria-expanded":e},t?{"aria-controls":t}:{},{role:"button",class:l.a`
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

        ${e?l.a`
                .fa-chevron-down {
                  transform: rotate(-180deg);
                }
              `:""}

      `},n),n.children,Object(r.h)(R,{type:"chevron-down"})),N=({head:e,children:t,id:n,...i})=>{const[o,a]=Object(c.g)(!1);return Object(r.h)(D,{class:i.class},Object(r.h)(A,{show:o,id:n,onClick:e=>{a(e=>!e)}},e),Object(r.h)(C,{show:o,id:n},t))};function _(){return(_=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}N.propTypes={head:p.a.node,children:p.a.node,class:p.a.string,id:p.a.string},N.defaultProps={};const E=e=>l.a`
  .navlist {
    list-style: none;
    display: flex;
    margin: 0;
    padding: 0;

    a {
      text-decoration: none;
    }

    > li {
      > a {
        display: block;

        svg.fa-chevron-down {
          transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

          &.open {
            transform: rotate(180deg);
          }
        }

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

        &.dropdown-open:after {
          width: 100%;
          width: calc(100% + 16px);
        }

        @media (min-width: ${e}) {
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

    .mobile-only {
      ${h}
    }

    @media (min-width: ${e}) {
      svg.fa-chevron-down {
        float: none;
        display: inline-block;
        font-size: 0.75rem;
        margin-left: 0.5rem;
      }
    }

    @media (max-width: ${e}) {
      flex-direction: column;
      align-items: stretch;
      padding: 0;

      > li {
        margin-right: 0;

        > a {
          padding: 1rem 2rem 0.3rem 2rem;
          justify-content: space-between;
          display: block;
          border-bottom: 1px solid #cccccc;
          align-items: center;

          > svg {
            float: right;
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

      .icon-nav-item {
        ${h}
      }

      .mobile-only {
        ${(e=>{const t=e||"relative";return l.a`
    width: auto;
    height: auto;
    margin: 0;
    overflow: visible;
    border: none;
    clip: auto;
    position: ${t};
  `})()}
      }
    }
  }
`,q=Object(c.c)(({children:e,...t},n)=>Object(r.h)("ul",_({ref:n,"aria-label":"ASU"},t,{class:Object(l.b)(t.class,"navlist")}),e)),W=e=>Object(r.h)("form",{class:"navbar-site-buttons"},e.children),U=e=>Object(r.h)("div",{class:Object(l.b)("dropdown",e.open?"open":"",e.class)},Object(r.h)("div",null,e.children)),X=e=>Object(r.h)("ul",{class:Object(l.b)("menu-column",e.open?"open":"")},e.children),B=l.a`
  .nav-icon {
    color: #191919;
  }
`,K=e=>l.a`
  ul {
    list-style: none;
    a {
      text-decoration: none;
    }
  }

  .mobile-only {
    ${h}
  }

  @media (min-width: ${e}) {
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

  @media (max-width: ${e}) {
    border: none;
    display: none;
    flex-direction: column;
    width: 100%;

    &.open-nav,
    &:target {
      overflow-y: scroll;
      display: flex;
    }
  }

  ${(e=>l.a`
  /** DdMenu CSS **/
  div.dropdown {
    max-height: 0;
    display: flex;
    z-index: 999;
    justify-content: space-between;
    background: #ffffff;
    flex-wrap: nowrap;
    transition: all 0.5s cubic-bezier(0.19, 1, 0.19, 1);
    margin: 0;
    padding: 0 1rem;
    border: 0;
    overflow: hidden;

    &.mega {
      width: 100%;
      left: 0;

      > div {
        max-width: ${"1224px"};
      }
    }

    &.open {
      max-height: 10000px;
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

    @media (max-width: ${e}) {
      padding-left: 3rem;
      flex-direction: column;

      &.open {
        position: relative;
      }
    }

    @media (min-width: ${e}) {
      position: fixed;

      > div {
        padding: 2rem;
        display: flex;
        margin: 0 auto;
      }

      &.open {
        border-bottom: 1px solid #d0d0d0;
      }

      margin-top: 1px;
      border-left: 1px solid #d0d0d0;
      border-right: 1px solid #d0d0d0;

      h3 {
        margin-top: 0;
      }
    }
  }
`)(e)}
  ${(e=>l.a`
  /** Dropdown Menu Column CSS **/
  ul.menu-column {
    display: flex;
    flex-direction: column;
    border-right: 1px solid #d0d0d0;
    padding: 0 2rem;
    margin-bottom: 3rem;

    :last-child {
      margin-bottom: 0;
      border-right: none;
    }

    @media (min-width: ${e}) {
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

    @media (max-width: ${e}) {
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

    @media (min-width: ${e}) {
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
`)(e)}
  ${(e=>l.a`
  form.navbar-site-buttons {
    display: flex;
    align-items: flex-end;
    padding-bottom: 3px;

    a + a {
      margin-left: 1rem;
    }

    @media (max-width: ${e}) {
      padding: 1rem 2rem;
    }
  }
`)(e)}
  ${E(e)}
  ${B}
`,G=e=>l.a`
  nav.header-nav {
    ${K(e)}
  }
`,J=({open:e,maxMobileHeight:t,injectStyles:n,breakpoint:i,handleKeyDown:o,children:a,...s})=>{const c=-1==t?"75vh":t+"px",d="Xl"===i?"1260px":"992px";return Object(r.h)("nav",_({id:"asu-header-nav",class:Object(l.b)("header-nav",e?"open-nav":"",l.a`
          @media (max-width: ${d}) {
            &.open-nav,
            &:target {
              flex-direction: column;
              width: 100%;

              max-height: ${c};
              display: flex;
            }
          }
        `,n?K(d):"")},s),a)};function V(){return(V=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Y=e=>l.a`
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

    @media (max-width: ${e}) {
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

    @media (min-width: ${e}) {
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
`,Q=e=>Object(r.h)("div",V({class:Object(l.b)("asu-search-form",e.class)},e),e.children),Z=e=>l.a`
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


    @media (min-width: ${e}) {
      margin-left: .5rem;
    }
  }
`,ee=e=>Object(r.h)("div",{class:Object(l.b)(e.class,"login-status")},e.children);function te(){return(te=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const ne=({children:e,breakpoint:t,...n})=>Object(r.h)("header",te({},n,{class:Object(l.b)(n.class,l.a`
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

          @media (max-width: ${t}) {
            &.scrolled .primary-nav .header-title h1 {
              font-size: 1rem;
            }
          }
        `,ce(t),G(t),f,de(t),he(t),oe(t),Y(t),ue(t),Z(t),re(t))}),e),re=e=>l.a`
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

    @media (min-width: ${e}) {
      display: none;
    }
  }
`,ie=({mobileOpen:e,...t})=>Object(r.h)("button",te({},t,{class:Object(l.b)(l.a`
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
        `,"navbar-toggler")}),e?Object(r.h)(R,{type:"circle-close"}):Object(r.h)(R,{type:"bars",href:"#asu-header-nav"})),oe=e=>l.a`
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

    @media (max-width: ${e}) {
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

  @media (min-width: ${e}) {
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
`,ae=e=>Object(r.h)("div",{class:Object(l.b)("universal-nav",e.open?"mobile-open":"",e.searchOpen?"search-open":""),ref:e.domRef},Object(r.h)("div",null,e.children)),se=({children:e,...t})=>Object(r.h)("div",{class:Object(l.b)("nav-grid",t.class)},e),ce=e=>l.a`
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

    @media (max-width: ${e}) {
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
`,le=e=>Object(r.h)("div",{class:"primary-nav"},Object(r.h)("div",null,e.children)),de=e=>l.a`
  .navbar-container {
    display: flex;
    width: 100%;
    flex-direction: column;
    align-items: flex-start;

    @media (max-width: ${e}) {
      width: 100%;
    }
  }
`,pe=e=>Object(r.h)("div",{class:Object(l.b)("navbar-container",e.class)},e.children),he=e=>l.a`
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

    @media (max-width: ${e}) {
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

  @media (max-width: ${e}) {
    &.scrolled .primary-nav .navbar-brand d img {
      height: 28px;
    }

    &.scrolled .navbar-brand .horiz {
      margin-bottom: 0.5rem;
    }
  }
`,be=e=>{const t=e.brandLink?e.brandLink:"https://asu.edu";return Object(r.h)("a",{href:t,class:"navbar-brand",ref:e.domRef},Object(r.h)("img",{class:"vert",src:e.src,alt:e.alt}),Object(r.h)("img",{class:"horiz",src:e.mobileSrc}))},ue=e=>l.a`
  .title {
    line-height: 1;
    font-size: 1rem;
    font-weight: 700;
    padding: 0 2rem 1.5rem 2rem;
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

    > a {
      display: none;
    }

    @media (min-width: ${e}) {
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

  @media (min-width: ${e}) {
    &.scrolled .title.subdomain-name {
      font-size: 1.5rem;
    }

    &.scrolled .title {
      padding-bottom: 0;
    }
  }
`,fe=Object(c.c)(({title:e,unit:t,...n},i)=>t?Object(r.h)("div",{class:"title",ref:i},Object(r.h)("a",{class:"unit-name"},t),Object(r.h)("span",{class:"subdomain-name"},e)):Object(r.h)("div",{class:"title subdomain-name",ref:i},e));function me(){return(me=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const ge=l.a`
  font-weight: 700;
  text-align: left;
  opacity: 1;
  margin: 1rem 0;
  line-height: calc(100% + 0.12em);
`,Oe=({children:e,...t})=>Object(r.h)("h4",me({},t,{class:Object(l.b)(l.a`
          ${ge}
          font-size: 1.25rem;
          letter-spacing: -0.025em;
        `,t.class)}),e),ye=({children:e,...t})=>Object(r.h)("h3",me({},t,{class:Object(l.b)(l.a`
          ${ge}
          font-size: 1.5rem;
          letter-spacing: -0.035em;
        `,t.class)}),e),ve=({type:e,...t})=>{switch(e){case"h4":return Object(r.h)(Oe,{class:t.class},t.children);case"h3":return Object(r.h)(ye,{class:t.class},t.children);default:return""}};function je(){return(je=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}ve.propTypes={type:p.a.string.isRequired},ve.defaultProps={};const we=Object(c.c)(({onFocus:e,text:t,...n},i)=>Object(r.h)("a",je({},n,{class:Object(l.b)("nav-item",n.class)},e?{onFocus:e}:"",{ref:i}),t)),xe=Object(c.c)(({children:e,onFocus:t,type:n,...i},o)=>Object(r.h)("a",je({},i,{class:Object(l.b)("nav-icon",i.class)},t?{onFocus:t}:"",{ref:o}),Object(r.h)(R,{type:n,className:"icon-nav-item"}),Object(r.h)("span",{class:"mobile-only"},e)));function ke(){return(ke=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const $e=({onFocus:e,itemRef:t,type:n,text:i,href:o,...a})=>{let s="";switch(n){case"button":s=Object(r.h)(g,ke({},a,{class:"nav-button",ref:t,href:o},e?{onFocus:e}:"",{medium:!0,dark:!0}),i);break;case"icon":s=Object(r.h)(xe,ke({},a,{href:o},e?{onFocus:e}:"",{ref:t,type:a.class}),i);break;case"heading":return Object(r.h)(ve,{type:"h3"},i);default:s=Object(r.h)(we,ke({href:o},e?{onFocus:e}:"",{ref:t},a),i)}return Object(r.h)("li",null,s)};$e.propTypes={itemRef:p.a.oneOfType([p.a.func,p.a.shape({current:p.a.instanceOf(p.a.element)})]),location:p.a.array,onFocus:p.a.func,type:p.a.string,href:p.a.string,text:p.a.string.isRequired,icon:p.a.string},$e.defaultProps={};var ze=$e;function Pe(){return(Pe=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Se=Object(c.c)(({text:e,setFocus:t,pIndex:n,isOpen:i,setOpen:o,children:a,mega:s,...c},l)=>{const d=e=>{o(i?-1:e)};return Object(r.h)("li",null,Object(r.h)("a",Pe({},c,{role:"button",class:i?"dropdown-open":"","aria-expanded":i,onMouseDown:e=>{e.preventDefault(),d(n)},onKeyDown:e=>{const t=e.keyCode;32!=t&&13!=t||d(n)},onFocus:e=>{t([n,-1,-1])},tabIndex:"0",ref:l}),e," ",Object(r.h)(x,{sr:e,className:i?"open":""})),Object(r.h)(U,Pe({open:i},{class:s?"mega":""}),a))});Se.propTypes={setFocus:p.a.func.isRequired,pIndex:p.a.number.isRequired,isOpen:p.a.bool,setOpen:p.a.func.isRequired,mega:p.a.bool,text:p.a.string},Se.defaultProps={isOpen:!1};var Te=Se;function Le(){return(Le=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Fe=({navTree:e,width:t,height:n,mobileOpen:i,maxMobileHeight:o,buttons:a,injectStyles:s,breakpoint:l,...d})=>{const[p,h]=Object(c.g)([-1,-1,-1]),[b,u]=Object(c.g)(-1),f=e=>{h(e)},m=parseInt("Xl"===l?"1260px":"992px",10),O=Object(c.e)(()=>e.map(e=>{const t=Object(c.a)();let n=[],{items:r,...i}=e;if(r&&r[0].length>0)for(let e=0;e<r.length;e++)for(let t=0;t<r[e].length;t++)if(n[e]||(n[e]=[]),n[e][t]=Object.assign({},r[e][t]),"heading"!=r[e][t].type){const r=Object(c.a)();n[e][t].ref=r}return{ref:t,item:i,menus:n}}),[e]);Object(c.d)(()=>{const e=Ie(p,O);if(e.hasFocus){const[t,n,r]=p;e.isTop?(O[t].ref&&O[t].ref.current!==document.activeElement&&O[t].ref.current.focus(),b!==t&&u(-1)):O[t].menus[n][r].ref&&O[t].menus[n][r].ref.current!==document.activeElement&&O[t].menus[n][r].ref.current.focus()}else-1!==b&&u(-1)},[p,O]);const y=Object(c.f)(null);Object(c.d)(()=>{const e=e=>{y.current&&!y.current.contains(e.target)&&u(-1)};return document.addEventListener("mousedown",e),()=>{document.removeEventListener("mousedown",e)}},[y]);return Object(r.h)(J,{open:i,maxMobileHeight:o,injectStyles:s,breakpoint:l},Object(r.h)(q,Le({},t>m?{onfocusout:e=>{e.currentTarget.contains(e.relatedTarget)||f([-1,-1,-1])}}:{},{onKeyDown:e=>{const t=Ie(p,O);if(t.hasFocus)switch(e.keyCode){case 37:e.preventDefault(),f(Re(p,t,O));break;case 39:e.preventDefault(),f(He(p,t,O));break;case 38:e.preventDefault(),f(Me(p,t,O));break;case 40:t.isTop&&t.hasSubs&&u(p[0]),e.preventDefault(),f(De(p,t,O));break;case 9:if(e.shiftKey){if(t.isFirst)return!1;e.preventDefault(),f(Re(p,t,O))}else{if(t.isLast)return!1;e.preventDefault(),f(He(p,t,O))}}},ref:y}),O.map((e,n)=>{const i=e.item,o=e.menus;return o&&o.length>0&&o[0].length>0?Object(r.h)(Te,{width:t,text:i.text,target:i.target,pIndex:n,setFocus:f,ref:e.ref,isOpen:b==n,setOpen:u,mobileWidth:m,mega:o.length>2},o.map((e,t)=>Object(r.h)(X,null,e.map((e,i)=>Object(r.h)(ze,{onFocus:()=>{h([n,t,i]),u(n)},itemRef:o[t][i].ref,type:e.hasOwnProperty("type")?e.type:void 0,color:e.hasOwnProperty("color")?e.color:void 0,class:e.hasOwnProperty("class")?e.class:void 0,href:e.hasOwnProperty("href")?e.href:void 0,text:e.text,tabIndex:"-1"}))))):Object(r.h)(ze,{onFocus:()=>{f([n,-1,-1])},itemRef:e.ref,type:i.hasOwnProperty("type")?i.type:void 0,color:i.hasOwnProperty("color")?i.color:void 0,class:i.hasOwnProperty("class")?i.class:"",href:i.hasOwnProperty("href")?i.href:void 0,text:i.text})})),a.length>0&&Object(r.h)(W,null,a.map((e,t)=>{let n=e.color?e.color:"maroon";return Object(r.h)(g,Le({href:e.href},{[n]:!0},{medium:!0}),e.text)})))};Fe.propTypes={navTree:p.a.arrayOf(p.a.object),buttons:p.a.arrayOf(p.a.object),mobileOpen:p.a.bool,width:p.a.number,height:p.a.number,maxMobileHeight:p.a.number,injectStyles:p.a.bool,breakpoint:p.a.oneOf(["Lg","Xl"])},Fe.defaultProps={navTree:[],mobileOpen:!1,width:1920,height:1080,maxMobileHeight:-1,buttons:[],injectStyles:!1};const Ie=(e,t)=>{const[n,r,i]=e;let o=!1,a=!1,s=!1,c=!1,l=!1;return-1==n&&-1==r&&-1==i?{hasFocus:o}:(o=!0,t[n].menus.length>0&&(s=!0),a=-1===r||-1===i,a&&n===t.length-1&&(c=!0),a&&0===n&&(l=!0),{hasFocus:o,isTop:a,hasSubs:s,isLast:c,isFirst:l})},Re=(e,t,n)=>{const[r,i,o]=e;let a=e;return t.isTop?(a=void 0!==n[r-1]?[r-1,-1,-1]:[0,-1,-1],!1===Ce(a,n)?Re(a,Ie(a,n),n):a):void 0!==n[r].menus[i-1]?n[r].menus[i-1][0].ref?[r,i-1,0]:[r,i-1,1]:[r,-1,-1]},He=(e,t,n)=>{const[r,i,o]=e;let a=e;return t.isTop?(a=void 0!==n[r+1]?[r+1,-1,-1]:[n.length-1,-1,-1],!1===Ce(a,n)?He(a,Ie(a,n),n):a):void 0!==n[r].menus[i+1]?n[r].menus[i+1][0].ref?[r,i+1,0]:[r,i+1,1]:[r,-1,-1]},Me=(e,t,n)=>{const[r,i,o]=e;let a=[],s=e;return t.hasSubs&&(a=n[r].menus),s=t.isTop?Re(e,t,n):void 0!==a[i][o-1]?[r,i,o-1]:[r,-1,-1],!1===Ce(s,n)?Me(s,Ie(s,n),n):s},De=(e,t,n)=>{const[r,i,o]=e;let a=[],s=e;return t.hasSubs&&(a=n[r].menus),s=t.isTop&&t.hasSubs?[r,0,0]:t.isTop?He(e,t,n):void 0!==a[i][o+1]?[r,i,o+1]:He(e,t,n),!1===Ce(s,n)?De(s,Ie(s,n),n):s},Ce=(e,t)=>{const n=Ie(e,t);if(!n.hasFocus)return!1;if(n.isTop){if(t[e[0]].ref)return!0}else if(t[e[0]].menus[e[1]][e[2]].ref)return!0;return!1};function Ae(){return(Ae=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Ne=({type:e,open:t,inputRef:n,mobile:i,...o})=>{switch(e){case"d7":return Object(r.h)("div",null,"Drupal 7");default:return Object(r.h)("form",{action:"https://search.asu.edu/search",method:"get",role:"search",class:t?"show-search-input":""},Object(r.h)("input",Ae({name:"q",type:"search"},n?{ref:n}:{},{"aria-labelledby":"asu-search-label"},i?{placeHolder:"Search ASU"}:{},{required:!0})),Object(r.h)("label",{class:"univeral-search",id:"asu-search-label"},"Search ASU"))}};Ne.propTypes={type:p.a.string,open:p.a.bool,inputRef:p.a.oneOfType([p.a.func,p.a.shape({current:p.a.instanceOf(p.a.element)})]),mobile:p.a.bool},Ne.defaultProps={};const _e=({type:e,open:t,setOpen:n,mobile:i})=>{const o=Object(c.f)(null);return Object(r.h)(Q,{onfocusin:()=>n(!0),onfocusout:e=>{o.current.value||e.currentTarget.contains(e.relatedTarget)||n(!1)},onClick:e=>{n(!0),o.current.focus()}},Object(r.h)(Ne,{open:t,type:e,inputRef:o,mobile:i}))};_e.propTypes={type:p.a.string,open:p.a.bool,setOpen:p.a.func,mobile:p.a.bool},_e.defaultProps={open:!1};const Ee=({loggedIn:e,loginLink:t,logoutLink:n,userName:i,...o})=>Object(r.h)(ee,{class:o.class},e?Object(r.h)(r.b,null,i?Object(r.h)("span",{class:"name"},i):"",Object(r.h)("a",{class:"signout",href:n},"Sign Out")):Object(r.h)("a",{href:t},"Sign in"));function qe(){const e="undefined"!=typeof window,{innerWidth:t,innerHeight:n}=e?window:{innerWidth:1920,innerHeight:1080};return{width:t,height:n}}function We(){return(We=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}Ee.propTypes={class:p.a.string,loggedIn:p.a.bool.isRequired,loginLink:p.a.string,logoutLink:p.a.string,userName:p.a.string},Ee.defaultProps={logoutLink:"https://webapp4.asu.edu/myasu/Signout",loginLink:"https://weblogin.asu.edu/cgi-bin/login",loggedIn:!1};const Ue=({navTree:e,title:t,unit:n,logo:i,loggedIn:o,userName:a,loginLink:s,logoutLink:l,buttons:d,breakpoint:p,...h})=>{const[b,u]=Object(c.g)(!1),[f,m]=Object(c.g)(!1),[g,O]=Object(c.g)(-1),y="Xl"===p?"1260px":"992px",v=parseInt(y,10),{height:j,width:w}=function(){const[e,t]=Object(c.g)(qe());return Object(c.d)(()=>{function e(){t(qe())}return window.addEventListener("resize",e),()=>window.removeEventListener("resize",e)},[]),e}(),[x,k]=Object(c.g)(0),$=()=>{const e=window.pageYOffset;k(e)},z=parseInt("24px",10),P=Object(c.f)(null),S=Object(c.f)(null),T=Object(c.f)(null);return Object(c.d)(()=>(window.addEventListener("scroll",$,{passive:!0}),()=>{window.removeEventListener("scroll",$)}),[]),Object(c.d)(()=>{w<v&&b&&window.setTimeout(()=>{const e=P.current.clientHeight,t=S.current.clientHeight,n=T.current.clientHeight;O(j-e-(t+n+z))},500)},[j,w,b]),Object(r.h)(ne,{breakpoint:y,class:x>0||b&&w<v?"scrolled":""},Object(r.h)(ae,We({open:b,domRef:P},{searchOpen:f}),Object(r.h)(se,null,Object(r.h)("a",{href:"https://www.asu.edu/"},"ASU home"),Object(r.h)("a",{href:"https://my.asu.edu/"},"My ASU"),Object(r.h)("a",{href:"https://www.asu.edu/colleges/"},"Colleges and schools"),Object(r.h)(Ee,{loggedIn:o,loginLink:s,logoutLink:l,userName:a})),Object(r.h)(_e,{open:f,setOpen:m,mobile:w<v})),Object(r.h)(le,null,h.dangerouslyGenerateStub?Object(r.h)("div",{id:"asu-generated-stub"}):Object(r.h)(r.b,null,Object(r.h)(be,We({},i,{domRef:S})),Object(r.h)(ie,{onClick:e=>{e.preventDefault(),u(e=>!e)},mobileOpen:b}),Object(r.h)(pe,null,Object(r.h)(fe,We({title:t,unit:n},{ref:T})),Object(r.h)(Fe,{navTree:e,logo:i,mobileOpen:b,height:j,width:w,buttons:d,maxMobileHeight:g,breakpoint:p})))))};Ue.propTypes={navTree:p.a.arrayOf(p.a.object),logo:p.a.shape({alt:p.a.string,src:p.a.string,mobileSrc:p.a.string,brandLink:p.a.string}),title:p.a.string,unit:p.a.string,loggedIn:p.a.bool,userName:p.a.string,loginLink:p.a.string,logoutLink:p.a.string,buttons:p.a.arrayOf(p.a.object),breakpoint:p.a.oneOf(["Lg","Xl"])},Ue.defaultProps={navTree:[],dangerouslyGenerateStub:!1,logo:{alt:"Arizona State University",src:"https://i.imgur.com/5WtkgkV.png",mobileSrc:"https://www.asu.edu/asuthemes/4.10/assets/arizona-state-university-logo.png"},title:"",unit:"",loggedIn:Ee.defaultProps.loggedIn,loginLink:Ee.defaultProps.loginLink,logoutLink:Ee.defaultProps.logoutLink,buttons:[],breakpoint:"Lg"};const Xe=e=>Object(r.h)("div",{class:Object(l.b)(e.class,l.a`
          padding: 2rem;
          margin-bottom: 2rem;
          border-radius: 0.3rem;
          border: 1px solid #dee2e6;
        `)},e.children),Be=e=>Object(r.h)(Xe,{class:e.class},e.children);Be.propTypes={class:p.a.string},Be.defaultProps={}}})}));