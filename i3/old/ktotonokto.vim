hi clear
if exists("syntax_on")
  syntax reset
endif
let g:colors_name="ktotonokto"
set background=dark

set guifont=Monospace:h14
hi Normal      ctermbg=NONE guibg=NONE
hi Type        ctermfg=green cterm=bold guifg=#58ff55 gui=bold
hi PreProc     ctermfg=blue cterm=bold guifg=#3f5df7 gui=bold
hi Constant    ctermfg=magenta cterm=bold guifg=#ff00ff gui=bold
hi Number      ctermfg=magenta cterm=bold guifg=#ff00ff gui=bold
hi String      ctermfg=magenta cterm=bold guifg=#ff00ff gui=bold
hi Identifier  ctermfg=14 guifg=#00ffff
hi Function    ctermfg=6 guifg=#00ffff
hi Statement   ctermfg=3 guifg=#ffff00
hi Special     ctermfg=red guifg=#ff0000
hi Comment     ctermfg=cyan cterm=bold guifg=#00ffff gui=bold
