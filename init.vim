call plug#begin('~/.vim/plugged')
Plug 'junegunn/vim-plug'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
call plug#end()

syntax on
colorscheme ktotonokto
highlight Cursorline cterm=bold

set background=dark
set ignorecase
set mouse=
set tabstop=2
set shiftwidth=2
set expandtab
set relativenumber
set number
set noswapfile
set linebreak
set list
set wrap
set ai
set cursorline
set softtabstop=2
set langmap=ФИСВУАПРШОЛДЬТЩЗЙКЫЕГМЦЧНЯ;ABCDEFGHIJKLMNOPQRSTUVWXYZ,фисвуапршолдьтщзйкыегмцчня;abcdefghijklmnopqrstuvwxyz
set encoding=utf-8
set nobackup
set nowritebackup
set updatetime=300
set signcolumn=yes

nnoremap <C-m> :!make<CR>
inoremap <silent><expr> <TAB>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<Tab>" :
      \ coc#refresh()
inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"
inoremap <silent><expr> <CR> coc#pum#visible() ? coc#pum#confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"
function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction
if has('nvim')
  inoremap <silent><expr> <c-space> coc#refresh()
else
  inoremap <silent><expr> <c-@> coc#refresh()
endif
