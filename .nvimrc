set makeprg=ninja\ -C\ build
let g:gtest#gtest_command = "build/tests/ServerTest"
nnoremap <silent> <leader>tt :GTestRun<CR>
nnoremap <silent> <leader>tu :GTestRunUnderCursor<CR>
nnoremap          <leader>tc :GTestCase<space>
nnoremap          <leader>tn :GTestName<space>
nnoremap <silent> <leader>te :GTestToggleEnabled<CR>
nnoremap <silent> ]T         :GTestNext<CR>
nnoremap <silent> [T         :GTestPrev<CR>
nnoremap <silent> <leader>tf :CtrlPGTest<CR>
nnoremap <silent> <leader>tj :GTestJump<CR>
nnoremap          <leader>ti :GTestNewTest<CR>i
