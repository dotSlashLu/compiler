/*
 *      Simple infix to postfix translator.
 *      Translation scheme:
 *              expr    ->      expr + term      {print('+')}
 *                      |       expr - term      {print('-')}
 *                      |       term
 *
 *              term    ->      term * factor    {print('*')}
 *                      |       term / factor    {print('/')}
 *                      |       factor
 *
 *              factor  ->      ( expr )
 *                      |       num              {print(num.value)}
 *                      |       id               {print(id.lexeme)}
 *
 **/

int main(int argc, char **argv)
{

}
